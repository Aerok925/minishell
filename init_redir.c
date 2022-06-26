/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:24:13 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/02 13:24:15 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_redir(t_redir *redir)
{
	close(redir->main_in);
	close(redir->main_out);
	if (redir->my_in > 0)
		close(redir->my_in);
	if (redir->my_out > 0)
		close(redir->my_out);
	free(redir);
}

void	init_redir(t_redir *redir)
{
	if (redir->my_in > 0)
		dup2(redir->my_in, 0);
	if (redir->my_out > 0)
		dup2(redir->my_out, 1);
}

t_redir	*init_redirect(t_com *com, t_enpv *declare, int flag)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->main_in = dup(0);
	redir->main_out = dup(1);
	redirect_main(redir, com, declare);
	if (!flag)
	{
		com->fd_in = redir->my_in;
		com->fd_out = redir->my_out;
		close(redir->main_in);
		close(redir->main_out);
		free(redir);
		return (NULL);
	}
	if (redir->my_out == -1 || redir->my_in == -1)
	{
		error_redir(redir);
		return (NULL);
	}
	else if (flag)
		init_redir(redir);
	return (redir);
}
