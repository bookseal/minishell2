#include "main.h"

// // Expands a line based on environment variables
// static char	*line_expansion(char *line, t_env *env_lst)
// {
// 	t_token	*tmp;
// 	char	*str;

// 	// Allocate memory for a new token
// 	tmp = (t_token *)malloc(sizeof(t_token));
// 	if (tmp == 0)
// 		return (0);
// 	tmp->value = line;
// 	tmp->type = 'w';
	
// 	// Allocate and initialize quote field of the token
// 	tmp->quote = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
// 	if (tmp->quote == 0)
// 		return (0);
// 	tmp->quote[ft_strlen(line)] = '\0';
// 	tmp->quote = (char *)ft_memset(tmp->quote, '0', ft_strlen(line));
	
// 	// Set next token as null and perform variable expansion
// 	tmp->next = 0;
// 	p_expansion(tmp, env_lst);
	
// 	// Deallocate quote field and return expanded value
// 	free(tmp->quote);
// 	str = tmp->value;
// 	free(tmp);
// 	return (str);
// }

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	loop_heredoc(char *end, t_cmd *cmd, t_env *env_lst, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, end, ft_strlen(end) + 1) == 0)
			break ;
		// TODO: heredoc in quotes
		// if (cmd->delimitor == 'h')
		// 	line = line_expansion(line, env_lst);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	open_heredoc(char *end, t_cmd *cmd, t_env **env_lst, int *fd_pipe)
{
	signal(SIGINT, signal_handler_heredoc);
	close(fd_pipe[0]);
	loop_heredoc(end, cmd, *env_lst, fd_pipe[1]);
	close(fd_pipe[1]);
	exit(0);
}

static int	dup_heredoc(t_cmd *cmd, int *fd_pipe)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	close(fd_pipe[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			cmd->fd_in = dup(fd_pipe[0]);
		close(fd_pipe[0]);
	}
	if (set_terminal())
		return (1);
	set_signal();
	return (0);
}

int	handle_heredoc(t_token *token, t_cmd *cmd, t_env **env_lst)
{
	int	pid;
	int	fd_pipe[2];
	int	i;

	token->need_to_del = TRUE;
	i = pipe(fd_pipe);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		open_heredoc(token->value, cmd, env_lst, fd_pipe);
	else
		dup_heredoc(cmd, fd_pipe);
		// return (parent_heredoc(cmd, fd_pipe));
	return (0);
}
