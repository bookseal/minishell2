#include "main.h"

int	is_option_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (str[i++] == 'n')
			continue ;
		else
			break ;
	}
	if (i != 0 && str[i] == '\0')
		return (1);
	return (0);
}

void	print_argv(t_cmd *cmd, int i)
{
	int	is_first_str;

	is_first_str = TRUE;
	while (cmd->argv[i] != 0)
	{
		if (is_first_str == FALSE)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->argv[i], 1);
		is_first_str = FALSE;
		i++;
	}
}

int	built_in_echo(t_cmd *cmd, t_env **env_lst)
{
	int	option_n;
	int	i;

	if (cmd->argv[1] == 0)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	option_n = FALSE;
	i = 1;
	while (cmd->argv[i] != 0)
	{
		if (is_option_n(cmd->argv[i]))
		{
			i++;
			option_n = TRUE;
			break ;
		}
		i++;
	}
	if (option_n == FALSE)
		i = 1;
	print_argv(cmd, i);
	if (option_n == FALSE)
		ft_putchar_fd('\n', 1);
	return (0);
}
