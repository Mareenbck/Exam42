#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

fd_set rfds, wfds, afds;
int max_fd = 0;
int count = 0;
char *msgs[65336];
int ids[65336];
char write_buf[1001];
char read_buf[42];

int extract_message(char **buf, char **msg)
{
	char *newbuf;
	int i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char *newbuf;
	int len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

/////////////////////////////////////////////////

void fatal_error()
{
	write(2, "Fatal Error\n", strlen("Fatal Error\n"));
	exit(1);
}

int create_socket()
{
	max_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (max_fd < 0)
		fatal_error();
	FD_SET(max_fd, &afds);
	return max_fd;
}

void notify_other(int author, char *str)
{
	for (int fd = 0; fd <= max_fd; fd++)
	{
		if (fd != author && FD_ISSET(fd, &wfds))
			send(fd, str, strlen(str), 0);
	}
}

void add_client(int client_fd)
{
	if (client_fd > max_fd)
		max_fd = client_fd;
	ids[client_fd] = count++;
	msgs[client_fd] = NULL;
	FD_SET(client_fd, &afds);
	sprintf(write_buf, "server: client %d just arrived\n", ids[client_fd]);
	notify_other(client_fd, write_buf);
}

void remove_client(int fd)
{
	sprintf(write_buf, "server: client %d just left\n", ids[fd]);
	notify_other(fd, write_buf);
	FD_CLR(fd, &afds);
	free(msgs[fd]);
	msgs[fd] = NULL;
	close(fd);
}

void send_messages(int fd)
{
	char *msg;

	while(extract_message(&(msgs[fd]), &msg))
	{
		sprintf(write_buf, "client % d: ", ids[fd]);
		notify_other(fd, write_buf);
		notify_other(fd, msg);
		free(msg);
		msg = NULL;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments"));
		exit(1);
	}

	FD_ZERO(&afds);
	int sockfd = create_socket();

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal_error();
	if (listen(sockfd, SOMAXCONN) != 0)
		fatal_error();

	while (1)
	{
		rfds = wfds = afds;

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &rfds))
				continue;
			if (fd == sockfd)
			{
				socklen_t len = sizeof(servaddr);
				int client_fd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
				if (client_fd >= 0)
				{
					add_client(client_fd);
					break;
				}
			}
			else
			{
				int read_bytes = recv(fd, &read_buf, 1024, 0);
				if (!read_bytes)
				{
					remove_client(fd);
					break;
				}
				read_buf[read_bytes] = '\0';
				msgs[fd] = str_join(msgs[fd], read_buf);
				send_messages(fd);
			}
		}
	}
	return 0;
}
