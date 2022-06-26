/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:58:08 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/01 22:13:34 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_to_array(char **opt, char **arg)
{
	int		i;
	char	**arr;
	int		y;

	arr = malloc(sizeof(char *) * (size_of_array_char(opt)
				+ size_of_array_char(arg) + 1));
	i = 0;
	y = 0;
	while (opt[y])
	{
		arr[i++] = copy_str(opt[y], 0, ft_strlen(opt[y]));
		y++;
	}
	y = 0;
	while (arg[y])
	{
		arr[i++] = copy_str(arg[y], 0, ft_strlen(arg[y]));
		y++;
	}
	free_arr(opt);
	arr[i++] = NULL;
	return (arr);
}

int	check_first_arg(char *str)
{
	int		i;
	int		minus;

	i = 0;
	minus = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	if (ft_strlen(&str[i]) > 19 || str[i] == 0)
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			break ;
	}
	if ((size_t)i != ft_strlen(str))
		return (0);
	return (1);
}

void	numeric_argument_required(t_enpv *my_envp, t_enpv *declare,
		char *line, char **arg)
{
	fd_putstr("exit\n", 2);
	fd_putstr("minishell: exit: ", 2);
	fd_putstr(arg[0], 2);
	fd_putstr(": numeric argument required\n", 2);
	free_arr(arg);
	free_lst(my_envp);
	free_lst(declare);
	free(line);
	exit(255);
}

unsigned char	final_check(t_enpv *my_envp, t_enpv *declare,
				char *line, char **arg)
{
	int					i;
	int					minus;
	unsigned long long	number;

	i = 0;
	minus = 1;
	number = 0;
	if (arg[0][i] == '-' || arg[0][i] == '+')
	{
		if (arg[0][i] == '-')
			minus *= -1;
		i++;
	}
	while (arg[0][i])
	{
		number = number * 10 + (arg[0][i] - '0');
		i++;
	}
	if (minus == -1 && number > ULONG_MAX / 2UL + 1UL)
		numeric_argument_required(my_envp, declare, line, arg);
	else if (number > 9223372036854775807 && minus == 1)
		numeric_argument_required(my_envp, declare, line, arg);
	return ((unsigned char)(number * minus));
}

void	exec_exit(t_enpv *my_envp, t_enpv *declare, char *line, t_mini *mini)
{
	char			**arg;
	unsigned char	code_exit;
	t_com			*command;

	command = mini->com;
	if (command->options == NULL && command->arg == NULL)
	{
		free_exit(my_envp, declare, line, mini);
		exit(0);
	}
	arg = exit_help(command);
	if (check_first_arg(arg[0]) == 0)
		numeric_argument_required(my_envp, declare, line, arg);
	code_exit = final_check(my_envp, declare, line, arg);
	if (arg[1] != NULL)
	{
		fd_putstr("minishell: exit: too many arguments\n", 2);
		free_arr(arg);
		free(get_adress_info(declare, "?")->info);
		get_adress_info(declare, "?")->info = int_to_str(1);
		return ;
	}
	free_exit(my_envp, declare, line, mini);
	exit(code_exit);
}
