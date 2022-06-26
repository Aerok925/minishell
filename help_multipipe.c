/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_multipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:32:53 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/06 19:32:54 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_multipipe(t_mini *mini)
{
	t_com	*temp;

	temp = mini->com;
	while (temp)
	{
		if (temp->fd_in > 0)
			close(temp->fd_in);
		if (temp->fd_out > 0)
			close(temp->fd_out);
		temp = temp->next;
	}
}

void	wait_multipipe(t_mini *mini)
{
	t_com	*temp;
	int		status;

	temp = mini->com;
	while (temp->next)
		temp = temp->next;
	waitpid(temp->pidor, &status, 0);
	g_kost = 0;
	temp = mini->com;
	while (temp->next)
	{
		if (!waitpid(temp->pidor, &status, WNOHANG))
		{
			kill(temp->pidor, SIGKILL);
			waitpid(temp->pidor, &status, 0);
		}
		temp = temp->next;
	}
}

void	refresh_fd(int tmpin, int tmpout, int fdin, int fdout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	close(fdout);
	close(fdin);
}

void	pipe_multipipe(int	*fdout, int *fdin)
{
	int	p[2];

	close(*fdout);
	pipe(p);
	*fdout = p[1];
	*fdin = p[0];
}

void	child_process(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	lst = dis_command_for_pipe(lst, mini, declare, line);
	exit(0);
}
