/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:12:53 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/19 21:04:44 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_lst_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '/')
		return (1);
	return (0);
}

int	check_arg_123(t_com *command)
{
	int		fd;
	int		r;
	char	c;
	int		ret_value;

	fd = open(command->arg[0], O_RDONLY);
	if (fd < 0)
	{
		ret_value = -1;
	}
	else
	{
		r = read(fd, &c, 0);
		if (r == 0)
			ret_value = -1;
		else if (check_lst_char(command->arg[0]) == 1)
		{
			ret_value = -2;
		}
		else
			ret_value = -1;
	}
	close(fd);
	return (ret_value);
}

void	perm_den(t_enpv *declare, t_com *com)
{
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(126);
	fd_putstr("minishell: ", 2);
	fd_putstr(com->arg[0], 2);
	fd_putstr(": Permission denied\n", 2);
}

void	no_such(t_enpv *declare, t_com *com)
{
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(127);
	fd_putstr("minishell: ", 2);
	fd_putstr(com->arg[0], 2);
	fd_putstr(": No such file or directory\n", 2);
}

void	exec_env(t_enpv *lst, t_com *command, t_enpv *declare)
{
	t_enpv	*next;

	if (command->arg)
	{
		if (check_arg_123(command) == -2)
			perm_den(declare, command);
		else
			no_such(declare, command);
		return ;
	}
	if (get_adress_info(lst, "_"))
	{
		next = get_adress_info(lst, "_");
		free(next->info);
		next->info = copy_str("/usr/bin/env", 0, 13);
	}
	else
	{
		lst_add_back(lst, "_", "/usr/bin/env");
		init_last_command(lst);
	}
	print_env(lst);
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(0);
}
