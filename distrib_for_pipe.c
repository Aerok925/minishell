/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_for_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:35:25 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/06 17:35:27 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_on_for_pipe(t_ready_command *rd_com)
{
	if (execve(rd_com->path_comand, rd_com->options, rd_com->env) == -1)
	{
		perror("execve");
		free_struct_ready_command(rd_com);
		return ;
	}
}

void	init_struct_for_pipe(t_enpv *env, t_enpv *declare, t_com *command)
{
	t_ready_command	*ready_command;

	ready_command = malloc(sizeof(t_ready_command));
	ready_command->path_comand = NULL;
	ready_command->options = NULL;
	ready_command->env = NULL;
	create_path(env, ready_command, command);
	if (ready_command->path_comand == NULL)
	{
		error_path(declare, command, ready_command);
		return ;
	}
	create_options_for_command(command, ready_command);
	env_in_arr(env, ready_command);
	execve_on_for_pipe(ready_command);
}

t_enpv	*dis_command_for_pipe_help(t_mini *mini, t_enpv *lst, t_enpv *declare)
{
	t_com	*command;
	int		i;

	i = 0;
	command = mini->com;
	if (ft_cmp("cd", command->command))
		exec_cd(lst, declare, command);
	else if (ft_cmp("echo", command->command))
	{
		exec_echo(command, declare);
	}
	else if (ft_cmp("unset", command->command) && command->arg)
	{
		check_arg_for_unset(command->arg, declare);
		while (command->arg[i])
			lst = del_elem_lst(lst, command->arg[i++]);
	}
	else
		init_struct_for_pipe(lst, declare, command);
	return (lst);
}

t_enpv	*dis_command_for_pipe(t_enpv *lst, t_mini *mini, t_enpv *declare,
			char *line)
{
	int		i;
	t_com	*command;

	command = mini->com;
	i = 0;
	small_letter(command);
	if (command->command == NULL)
		exit (0);
	if (command->fd_in == -1 || command->fd_out == -1)
		exit(1);
	if (command->fd_in > 0)
		dup2(command->fd_in, 0);
	if (command->fd_out > 0)
		dup2(command->fd_out, 1);
	if (ft_cmp("pwd", command->command))
		exec_pwd(declare);
	else if (ft_cmp("exit", command->command))
		exec_exit(lst, declare, line, mini);
	else if (ft_cmp("env", command->command))
		exec_env(lst, command, declare);
	else if (ft_cmp("export", command->command))
		exec_branch(lst, command, declare);
	else
		lst = dis_command_for_pipe_help(mini, lst, declare);
	exit(errno);
}
