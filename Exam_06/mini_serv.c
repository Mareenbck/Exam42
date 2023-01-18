#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <sys/select.h>

//us pouvez utiliser n'importe quel port au dessus de 1024 jusqu'à 65535

fd_set	rfds, wfds, afds;
int		max_fd = 0;
int		count = 0;
int		ids[65536];
char	*msgs[65536];
char	buf_write[42];
char	buf_read[1001];


// START COPY-PASTE FROM GIVEN MAIN

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

// END COPY-PASTE

void fatal_error()
{
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

int	create_socket(void)
{

	//creer un fd de socket qui pourra etre utilise plus tard
	max_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (max_fd < 0)
		fatal_error();
	//ajouter le fd de socket dans le fd_set
	FD_SET(max_fd, &afds);
	return max_fd;

}

void notify_other(int author, char *str)
{
	for (int fd = 0; fd <= max_fd; fd++)
	{
		if (FD_ISSET(fd, &wfds) && fd != author)
			send(fd, str, strlen(str), 0);
	}
}

void register_client(int client_fd)
{
	if (client_fd > max_fd)
		max_fd = client_fd;
	ids[client_fd] = count++;
	msgs[client_fd]= NULL;
	FD_SET(client_fd, &afds);
	sprintf(buf_write, "server: client %d just arrived\n", ids[client_fd]);
	notify_other(client_fd, buf_write);
}

void remove_client(int fd)
{
	sprintf(buf_write, "server: client %d just left\n", ids[fd]);
	notify_other(fd, buf_write);
	free(msgs[fd]);
	msgs[fd] = NULL;
	FD_CLR(fd, &afds);
	close(fd);
}

void	send_msg(int fd)
{
	char *msg;

	while(extract_message(&(msgs[fd]), &msg))
	{
		sprintf(buf_write, "client %d: ", ids[fd]);
		notify_other(fd, buf_write);
		notify_other(fd, msg);
		free(msg);
		msg = NULL;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}
	//clear le fd_set
	FD_ZERO(&afds);
	int socket_fd = create_socket();

	// START COPY-PASTE FROM MAIN

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	// Binding newly created socket to given IP and verification
	// lier une adresse de socket a une socket
	if ((bind(socket_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal_error();
	// collecter les connexions entrantes dans une file d'attente.
	if (listen(socket_fd, SOMAXCONN) != 0)
		fatal_error();

	// END COPY-PASTE

	while (1)
	{
		rfds = wfds = afds;

		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			//check si fd est present dans rfds
			if (!FD_ISSET(fd, &rfds))
				continue;

			if (fd == socket_fd)
			{
				socklen_t addr_len = sizeof(servaddr);
				//récupérer la connection en attente et renvoi un nouveau fd a utiliser pour send
				int client_fd = accept(socket_fd, (struct sockaddr *)&servaddr, &addr_len);
				if (client_fd >= 0)
				{
					register_client(client_fd);
					break ;
				}
			}
			else
			{
					int read_bytes = recv(fd, buf_read, 1024, 0);
					if (read_bytes <= 0)
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
	return (0);
}
