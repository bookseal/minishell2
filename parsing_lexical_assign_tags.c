#include "main.h"

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
	if (token->tag > 1)
		token->next->tag = REDIRECT_INFO;
	return (0);
}

int assign_tags(t_token **tokens)
{
	t_token *token;

	token = *tokens;
	while (token)
	{
		if (token->tag == NEED_DECIDE && iterate_tags(token))
			return (print_error(token, "token"));
		token = token->next;
	}
	return (0);
}