/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ready__command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:40:24 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/19 20:40:54 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_path(t_enpv *declare, t_com *com, t_ready_command *ready)
{
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(127);
	fd_putstr("minishell: ", 2);
	fd_putstr(com->command, 2);
	fd_putstr(": command not found\n", 2);
	free(ready->path_comand);
	free(ready);
}

void	init_struct(t_enpv *env, t_enpv *declare, t_com *command)
{
	t_ready_command	*ready_command;

	ready_command = malloc(sizeof(t_ready_command));
	ready_command->path_comand = NULL;
	ready_command->options = NULL;
	ready_command->env = NULL;
	create_path(env, ready_command, command);
	g_kost = 2;
	if (ready_command->path_comand == NULL)
	{
		error_path(declare, command, ready_command);
		return ;
	}
	create_options_for_command(command, ready_command);
	env_in_arr(env, ready_command);
	execve_on(ready_command, declare);
}
