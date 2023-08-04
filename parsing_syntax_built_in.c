#include "main.h"

int	is_built_in(char *argv_0)
{
	const char *b[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	int i;

	i = 0;
	while (b[i])
	{
		if (!ft_strncmp(argv_0, b[i], ft_strlen(b[i]) + 1))
			return (i + 1);
		i++;
	}
	return (0);
}