#include "main.h"

int	built_in_env(t_env **env_lst)
{
	return (print_env_lst(env_lst, FALSE));
}
