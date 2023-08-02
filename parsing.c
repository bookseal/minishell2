#include "main.h"

int	parsing(char *input, t_cmd **cmds, t_env **env_lst)
{
	t_token	*tokens;

	if (lexical_analyzer(&tokens, input, env_lst))
	{
		token_clear(&tokens, &free);
		return (1);
	}
	if (syntax_analyzer(cmds, tokens, env_lst))
	{
		// TODO: cmds_clear(cmds, &free);
		return (1);
	}	
	return (0);
}
