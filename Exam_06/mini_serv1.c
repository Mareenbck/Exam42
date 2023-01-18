#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>

fd_set rfds, wfds, afds;
int max_fd = 0;
int count = 0;
int ids[65536];
char *msgs[65536];
char buf_write[1001];
char buf_read[42];

///////////////////////////////////////////////////////////
int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

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
	char	*newbuf;
	int		len;

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
///////////////////////////////////////////////////////////

void fatal_error()
{
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

int create_socket()
{
	max_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (max_fd <= 0)
		fatal_error();
	return max_fd;
}

void notify(int author, char *str)
{
	for (int fd = 0; fd <= max_fd; fd++)
	{
		if (FD_ISSET(author, &wfds) && fd != author)
			send(fd, str, strlen(str), 0);
	}
}

void register_client(int client_fd)
{
	if (client_fd > max_fd)
		max_fd = client_fd;
	ids[client_fd] = count++;
	msgs[client_fd] = NULL;
	FD_SET(client_fd, &rfds);
	sprintf(buf_write, "server: client %d just arrived\n", ids[client_fd]);
	notify(client_fd, buf_write);
}

void remove_client(int fd)
{
	sprintf(buf_write, "server: client %d just left\n",  ids[fd]);
	notify(fd, buf_write);
	free(msgs[fd]);
	msgs[fd] = NULL;
	FD_CLR(fd, &afds);
	close(fd);
}

void send_msg(int fd)
{
	char *str;

	while (extract_message(&(msgs[fd]), &msgs))
	{
		sprintf(buf_write, "client %d: ",  ids[fd]);
		notify(fd, buf_write);
		notify(fd, str);
		free(str);
		str = NULL;
	}
}

int main (int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	FD_ZERO(&afds);
	int sockfd = create_socket();

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal_error();
	if (listen(sockfd, SOMAXCONN) != 0)
		fatal_error();

	while(1)
	{
		rfds = wfds = afds;

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
			fatal_error();

		for(int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &rfds))
				continue;
			if (fd == sockfd)
			{
				socklen_t addr_len = sizeof(servaddr);
				int client_fd = accept(sockfd, (struct sockaddr *)&servaddr, &addr_len);
				if (client_fd >= 0)
				{
					register_client(client_fd);
					break;
				}
			}
			else
			{
				int read_bytes = recv(sockfd, buf_read, 1024, 0);
				if (!read_bytes)
				{
					remove_client(fd);
					break;
				}
				buf_read[read_bytes] = '\0';
				msgs[fd] = str_join(msgs[fd], buf_read);
				send_msg(fd);
			}
		}
	}
	return 0;
}
