#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define	STDIN 0
#define	STDOUT 1
#define	STDERR 2

#define	END 5
#define	PIPE 6
#define	BREAK 7

typedef struct s_cmd
{
	char **val;
	int len;
	int type;
	int fd[2];
	struct s_cmd *next;
	struct s_cmd *prev;
}	t_cmd;

//utils
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	char *new;
	int i = ft_strlen(str);

	new = malloc(sizeof(char) * i + 1);
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (--i >= 0)
		new[i] = str[i];
	return (new);
}

void ft_lst_addback(t_cmd **cmd, t_cmd *new)
{
	t_cmd *tmp;

	if (!(*cmd))
		*cmd = new;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void ft_free_lst(t_cmd *cmd)
{
	t_cmd *tmp;
	int i;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (i < cmd->len)
			free(cmd->val[i++]);
		free(cmd->val);
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

//errors
void	exit_fatal(void)
{
	write(STDERR, "fatal error\n", ft_strlen("fatal error\n"));
	exit(EXIT_FAILURE);
}

void	exit_execve(char *str)
{
	write(STDERR, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(STDERR, str, ft_strlen(str));
	write(STDERR, "\n", ft_strlen("\n"));
	exit(EXIT_FAILURE);
}

void	exit_cd_1(void)
{
	write(STDERR, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
	exit(EXIT_FAILURE);
}

void	exit_cd_2(char *str)
{
	write(STDERR, "error: cd: cannot change directory to", ft_strlen("error: cd: cannot change directory to"));
	write(STDERR, str, ft_strlen(str));
	write(STDERR, "\n", ft_strlen("\n"));
	exit(EXIT_FAILURE);
}

//parser
int check_size(char **av)
{
	int i = 0;

	while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
		i++;
	return (i);
}

int check_end(char *av)
{
	if (!av)
		return (END);
	if (strcmp(av, "|") == 0)
		return (PIPE);
	if (strcmp(av, ";") == 0)
		return (BREAK);
	return (0);
}

int parser(t_cmd **cmd, char **av)
{
	int size = check_size(av);
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_fatal();
	new->val = (char **)malloc(sizeof(t_cmd) * size + 1);
	if (!new->val)
		exit_fatal();
	new->val[size] = NULL;
	new->len = size;
	new->next = NULL;
	new->prev = NULL;
	new->type = check_end(av[size]);
	while (--size >= 0)
		new->val[size] = ft_strdup(av[size]);
	ft_lst_addback(cmd, new);
	return (new->len);
}

//execution
void ft_execution(t_cmd *cmd, char **envp)
{
	pid_t pid;
	int status;

	if (cmd->type == PIPE)
	{
		if (pipe(cmd->fd))
			exit_fatal();
	}
	pid = fork();
	if (pid < 0)
		exit_fatal();
	else if (pid == 0)
	{
		if (cmd->type == PIPE && dup2(cmd->fd[STDOUT], STDOUT) < 0)
			exit_fatal();
		if (cmd->prev && cmd->prev->type == PIPE && dup2(cmd->prev->fd[STDIN], STDIN) < 0)
			exit_fatal();
		if (execve(cmd->val[0], cmd->val, envp) < 0)
			exit_execve(cmd->val[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd->type == PIPE)
		{
			close(cmd->fd[STDOUT]);
			if (!cmd->next || cmd->type == BREAK)
				close(cmd->fd[STDIN]);
		}
		if (cmd->prev && cmd->prev->type == PIPE)
			close(cmd->prev->fd[STDIN]);
	}
}

void	ft_parse_exe(t_cmd *cmd, char **envp)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (strcmp("cd", tmp->val[0]) == 0)
		{
			if (tmp->len < 2)
				exit_cd_1();
			else if (chdir(tmp->val[1]))
				exit_cd_2(tmp->val[1]);
		}
		else
			ft_execution(tmp, envp);
		tmp = tmp->next;
	}
}

//main
int main(int ac, char **av, char **envp)
{
	int i = 1;
	t_cmd *cmd = NULL;

	if (ac <= 1)
		return (1);
	while (av[i])
	{
		while (av[i] && strcmp(av[i], ";") == 0)
			i++;
		if (av[i])
			i += parser(&cmd, &av[i]);
		if (!av[i])
			break ;
		else
			i++;
	}
	if (cmd)
		ft_parse_exe(cmd, envp);
	ft_free_lst(cmd);
	return (0);
}
