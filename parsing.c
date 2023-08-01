#include "main.h"

int	parsing(char *input, t_cmd **cmds, t_env **env_lst)
{
	t_token	*tokens;

	if (lexical_analyzer(&tokens, input, env_lst))
	{
		token_clear(&tokens, &free);
		return (1);
	}
	// TODO: syntax_analyzer(cmds, tokens, env_lst)
	return (0);
}
