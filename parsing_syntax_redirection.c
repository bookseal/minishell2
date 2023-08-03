#include "main.h"

// // Helper function for file opening
// static int	open_file(t_command *command, int flag, int std)
// {
// 	int	fd = open(command->oper_value, flag, 0644);
// 	if (command->std_out != std)
// 		close(command->std_out);
// 	return fd;
// }

// // Handling input redirection
// static int	parsing_ins(t_token **tokens, t_command *command, t_var **env_lst)
// {
// 	if (ft_strncmp(command->oper, "<", 2) == 0)
// 	{
// 		command->std_in = open_file(command, O_RDONLY, 0);
// 		if (command->std_in < 0) return (-1);
// 	}
// 	else if (ft_strncmp(command->oper, "<<", 3) == 0)
// 		return heredoc(command, env_lst);
// 	return (0);
// }

// // Handling output redirection
// static void	parsing_out(t_command *command)
// {
// 	command->std_out = open_file(command, O_CREAT | O_WRONLY | O_APPEND, 1);
// }

// // Handling redirections
// static int	parsing_redirs(t_token **tokens, t_command *command, t_token **tmp, t_var **env_lst)
// {
// 	command->oper_value = ft_strdup((*tokens)->value);
// 	command->delimitor = (*tokens)->type;
// 	*tokens = (*tokens)->next;
// 	if (ft_strncmp(command->oper, ">", 2) == 0)
// 		command->std_out = open_file(command, O_CREAT | O_WRONLY | O_TRUNC, 1);
// 	else if (ft_strncmp(command->oper, ">>", 3) == 0)
// 		parsing_out(command);
// 	else
// 		return parsing_ins(tokens, command, env_lst);
// 	return (0);
// }

// Parsing operators
int	handle_redirection(t_token **tokens, t_cmd *command, t_env **env_lst)
{
	int	status;
	
	status = 0;
	// while ((*tokens) != 0 && (*tokens)->tag != PIPE && status >= 0)
	// {
	// 	cmd->oper = ft_strdup((*tokens)->value);
	// 	*tokens = (*tokens)->next;
	// 	if (*tokens != 0 && ((*tokens)->type == 'v' || \
	// 				(*tokens)->type == 'h' || (*tokens)->type == 'H'))
	// 		status = parsing_redirs(tokens, command, NULL, env_lst);
	// 	else
	// 	{
	// 		ft_putstr_fd("Minishell$ Syntax error: Undefined value after operator\n", 2);
	// 		return (-2);
	// 	}
	// }
	return (status);
}
