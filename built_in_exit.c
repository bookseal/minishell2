#include "main.h"

static char	*atoa_removed_spaces_sign(char *str, int *sign)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			break ;
		else if (*str == '+')
		{
			str++;
			break ;
		}
		else if (*str == '-')
		{
			*sign = -1;
			str++;
			break ;
		}
		else if ((9 <= *str && *str <= 13) || *str == ' ')
			str++;
		else
			return (0);
	}
	return (str);
}

int	argv_to_status(const char *str)
{
	char				*num_str;
	int					s;
	unsigned long long	res[3];

	s = 1;
	num_str = atoa_removed_spaces_sign((char *)str, &s);
	if (num_str == 0 || *num_str == 0)
		return (1);
	res[0] = 0;
	res[1] = 0;
	while (*num_str != '\0')
	{
		if (!ft_isdigit(*num_str))
			return (1);
		res[0] = res[0] * 10 + (*num_str - '0');
		res[2] = res[0] / 10;
		res[2] -= (*num_str - '0') / 10;
		if (res[1] != res[2])
			return (1);
		res[1] = res[0];
		num_str++;
	}
	if ((s == 1 && res[0] > 2147483647) || (s == -1 && res[0] > 2147483648))
		return (1);
	g_exit_status = (int)(s * res[0]);
	return (0);
}

int	is_valid_argv_1(t_cmd *cmd)
{
	int		i;
	char	c;

	i = 0;
	c = cmd->argv[1][i];
	if (c == '-' || c == '+')
		i++;
	while (i < ft_strlen(cmd->argv[1]))
	{
		c = cmd->argv[1][i];
		if (!ft_isdigit(c))
			return (FALSE);
		i++;
	}
	if (argv_to_status(cmd->argv[1]))
		return (FALSE);
	return (TRUE);
}

void	exit_to_env_lst(t_env *env_lst)
{
	while (env_lst->tag != ENV_EXIT)
		env_lst = env_lst->next;
	if (env_lst->value)
		free(env_lst->value);
	env_lst->value = ft_strdup("exit");
	env_lst->exit_status = g_exit_status;
}

int	ft_get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		i++;
	}
	return (i);
}

int	built_in_exit(t_cmd *cmd, t_env **env_lst)
{
	int	argc;

	argc = ft_get_argc(cmd->argv);
	ft_putendl_fd("exit", 1);
	if (argc == 1)
		;
	else if (argc > 3)
	{
		print_error(NULL, "exit: too many arguments");
		g_exit_status = 1;
	}
	else if (!is_valid_argv_1(cmd))
	{
		print_error(NULL, "exit: Invalid exit arguments");
		g_exit_status = 255;
	}
	else
		argv_to_status(cmd->argv[1]);
	exit_to_env_lst(*env_lst);
	return (0);
}
