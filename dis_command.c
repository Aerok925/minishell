/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:29:43 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/06 19:29:44 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enpv	*dis_coomand_three(t_enpv *lst, t_mini *mini, t_enpv *declare)
{
	int		i;
	t_com	*command;

	command = mini->com;
	i = 0;
	if (ft_cmp("unset", command->command))
	{
		if (command->arg)
		{
			check_arg_for_unset(command->arg, declare);
			while (command->arg[i])
			{
				if (ft_strcmp(command->arg[i], "_") != 0)
					lst = del_elem_lst(lst, command->arg[i++]);
				else
					i++;
			}
		}
	}
	else
	{
		init_struct(lst, declare, command);
	}
	return (lst);
}

t_enpv	*dis_command_two(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line)
{
	t_com	*command;

	command = mini->com;
	if (ft_cmp("pwd", command->command))
		exec_pwd(declare);
	else if (ft_cmp("exit", command->command))
		exec_exit(lst, declare, line, mini);
	else if (ft_cmp("env", command->command))
		exec_env(lst, command, declare);
	else if (ft_cmp("export", command->command))
		exec_branch(lst, command, declare);
	else if (ft_cmp("cd", command->command))
		exec_cd(lst, declare, command);
	else if (ft_cmp("echo", command->command))
		exec_echo(command, declare);
	else
		lst = dis_coomand_three(lst, mini, declare);
	return (lst);
}

void	redir_check(t_redir *redir)
{
	if (redir != NULL)
	{
		dup2(redir->main_out, 1);
		dup2(redir->main_in, 0);
		if (redir->my_out > 0)
			close(redir->my_out);
		if (redir->my_in > 0)
			close(redir->my_in);
		close(redir->main_out);
		close(redir->main_in);
		free(redir);
	}
}

void	close_fd(t_redir *redir)
{
	if (redir && redir->my_out > 0)
	{
		dup2(redir->main_out, 1);
		close(redir->my_out);
	}
	if (redir && redir->my_in > 0)
	{
		dup2(redir->main_in, 0);
		close(redir->my_in);
	}
	if (redir)
	{
		close(redir->main_in);
		close(redir->main_out);
	}
}

t_enpv	*dis_command(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line)
{
	t_redir	*redir;
	t_com	*command;

	command = mini->com;
	redir = NULL;
	small_letter(command);
	if (command->flag > 0 || command->flag_heredoc > 0)
	{
		redir = init_redirect(command, declare, 1);
		if (redir == NULL)
			return (lst);
	}
	if (command->command == NULL)
	{
		close_fd(redir);
		free(redir);
		return (lst);
	}
	lst = dis_command_two(lst, mini, declare, line);
	redir_check(redir);
	add_to_(declare, command);
	return (lst);
}
