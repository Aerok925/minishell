/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:55:16 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/24 21:40:19 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_standart_fd(int *tmpin, int *tmpout, int *fdin, int *fdout)
{
	*tmpin = dup(0);
	*tmpout = dup(1);
	*fdin = dup(*tmpin);
	*fdout = dup(*tmpout);
}

void	while_close_fd(int *fdin, int *fdout, t_mini *mini, int tmpout)
{
	dup2(*fdin, 0);
	close(*fdin);
	if (mini->com->next == NULL)
		*fdout = dup(tmpout);
	else
		pipe_multipipe(fdout, fdin);
	dup2(*fdout, 1);
	close(*fdout);
	g_kost = 2;
}

int	check_fork(pid_t pid)
{
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else
		return (0);
}

void	pipe_command(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line)
{
	t_com	*temp;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;

	temp = mini->com;
	set_standart_fd(&tmpin, &tmpout, &fdin, &fdout);
	while (mini->com)
	{
		dup2(tmpin, 1);
		init_redirect(mini->com, declare, 0);
		while_close_fd(&fdin, &fdout, mini, tmpout);
		mini->com->pidor = fork();
		if (check_fork(mini->com->pidor))
			break ;
		if (mini->com->pidor == 0)
			child_process(lst, mini, declare, line);
		else
			mini->com = mini->com->next;
	}
	refresh_fd(tmpin, tmpout, fdin, fdout);
	mini->com = temp;
	wait_multipipe(mini);
	close_fd_multipipe(mini);
}

t_enpv	*distribution_command(t_enpv *lst, t_mini *mini, t_enpv *declare,
			char *line)
{
	if (!mini->com->next)
		lst = dis_command(lst, mini, declare, line);
	else
		pipe_command(lst, mini, declare, line);
	return (lst);
}
