#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>


typedef struct s_clients
{
	int	id;
	char msg[4096];
}	t_clients;

fd_set running, readfds, writefds;

t_clients	clients[4096];

int	fdmax = 0, nextid = 0;

char	buffread[4096 + 1], buffwrite[4096 + 1];

void	ft_error(char *str)
{
	if (str)
		write(2, str, strlen(str));
	else
		write(2, "Fatal error", strlen("Fatal error"));
	write(2, "\n", 1);
	exit(1);
}

void	ft_sendmsg(int fd)
{
	for (int i = 0; i <= fdmax; i++)
		if (FD_ISSET(i, &writefds) && i != fd)
			send(i, buffwrite, strlen(buffwrite), 0);
}

int main(int ac, char **av) {

	if (ac != 2)
		ft_error("Wrong number of arguments");

	// socket create and verification
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		ft_error(NULL);

	// setup fd list
	FD_ZERO(&running);
	bzero(&clients, sizeof(clients));
	fdmax = sockfd;
	FD_SET(sockfd, &running);

	// assign IP, PORT
	struct sockaddr_in servaddr;
	socklen_t			len;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		ft_error(NULL);
	if (listen(sockfd, 10) < 0)
		ft_error(NULL);

	while (1)
	{
		readfds = writefds = running;
		if (select(fdmax + 1, &readfds, &writefds, NULL, NULL) < 0)
			continue ;

		for (int i = 0; i <= fdmax; i++)
		{
			// accept
			if (FD_ISSET(i, &readfds) && i == sockfd)
			{
				int connfd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
				if (connfd < 0)
					continue ;
				if (connfd > fdmax)
					fdmax = connfd;
				clients[connfd].id = nextid++;
				FD_SET(connfd, &running);
				sprintf(buffwrite, "server: client %d just arrived\n", clients[connfd].id);
				ft_sendmsg(connfd);
				break ;
			}

			// receive and send
			if (FD_ISSET(i, &readfds) && i != sockfd)
			{
				int res = recv(i, buffread, 4096, 0);
				if (res <= 0)
				{
					sprintf(buffwrite, "server: client %d just left\n", clients[i].id);
					ft_sendmsg(i);
					FD_CLR(i, &running);
					close(i);
					break ;
				}
				else
				{
					for (int k = 0, j = strlen(clients[i].msg); k < res; k++, j++)
					{
						clients[i].msg[j] = buffread[k];
						if (clients[i].msg[j] == '\n')
						{
							clients[i].msg[j] = '\0';
							sprintf(buffwrite, "client %d: %s\n", clients[i].id, clients[i].msg);
							ft_sendmsg(i);
							bzero(&clients[i].msg, strlen(clients[i].msg));
							j = -1;
						}
					}
					break ;
				}
			}
		}
	}
	close(sockfd);
	return 0;
}
