#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void	putstr2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

int ft_execute(char **av, int i, char **env)
{
	av[i] = NULL;
	execve(av[0], av, env);
	putstr2("error: cannot execute ");
	putstr2(av[0]);
	write(2, "\n", 1);
	return (1);
}

int	main(int ac, char *av[], char *env[])
{
	int	i;
	int pid;
	int fd[2];
	int tmp;
	(void)ac;

	pid = 0;
	i = 0;
	tmp = dup(STDIN_FILENO);
	while (av[i] && av[i + 1]) 
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (strcmp(av[0], "cd") == 0) //cd
		{
			if (i != 2)
				putstr2("error: cd: bad arguments\n");
			else if (chdir(av[1]) != 0)
			{
				putstr2("error: cd: cannot change directory to ");
				putstr2(av[1]);
				write(2, "\n", 1);
			}
		}
		else if (i != 0 && (av[i] == NULL || strcmp(av[i], ";") == 0)) //exec ds stdout
		{
			pid = fork();
			if ( pid == 0)
			{
				dup2(tmp, STDIN_FILENO);
				close(tmp);
				if (ft_execute(av, i , env))
					return (1);
			}
			else
			{
				close(tmp);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
				tmp = dup(STDIN_FILENO);
			}
		}
		else if(i != 0 && strcmp(av[i], "|") == 0) //pipe
		{
			pipe(fd);
			pid = fork();
			if ( pid == 0)
			{
				dup2(tmp, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(tmp);
				if (ft_execute(av, i , env))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(tmp);
				tmp = fd[0];
			}
		}
	}
	close(tmp);
	return (0);
}