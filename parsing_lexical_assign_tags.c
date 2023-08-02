#include "main.h"

int	print_assign_tags_error(t_token *token)
{
	ft_putstr_fd("Syntax error: token", 2);
	ft_putendl_fd(token->value, 2);
	return (1);
}

int	iterate_tags(t_token *token)
{
	char	*str;

	str = token->value;
	if (!ft_strncmp(str, "|", 2))
		token->tag = PIPE;
	else if (!ft_strncmp(str, "<", 2))
		token->tag = REDIRECT_IN;
	else if (!ft_strncmp(str, ">", 2))
		token->tag = REDIRECT_OUT;
	else if (!ft_strncmp(str, "<<", 3))
		token->tag = HEREDOC;
	else if (!ft_strncmp(str, ">>", 3))
		token->tag = APPEND_OUT;
	else
		return (1);
	return (0);
}

int assign_tags(t_token **tokens)
{
	t_token *token;

	token = *tokens;
	while (token)
	{
		if (token->tag == NEED_DECIDE && iterate_tags(token))
			return (print_assign_tags_error(token));
		token = token->next;
	}
	return (0);
}