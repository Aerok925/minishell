/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:34:37 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/28 14:34:47 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_help_in_mini_part_one(t_com *com)
{
	int	j;

	j = 0;
	if (com->heredoc)
	{
		while (com->heredoc[j])
			ft_heredoc(com->heredoc[j++]);
	}
	return (j);
}

int	redir_help_in_mini_part_two(t_redir *rc, t_com *com, t_enpv *declare)
{
	int	i;

	i = 0;
	if (com->out_file != NULL)
	{
		while (com->out_file[i])
		{
			if (access(com->out_file[i], 0) == -1)
			{
				error_no_file(com->out_file[i], declare);
				rc->my_in = -1;
				return (-1);
			}
			else if (access(com->out_file[i], 4) == -1)
			{
				error_permisson_denaid(com->out_file[i], declare);
				rc->my_in = -1;
				return (-1);
			}
			i++;
		}
	}
	return (i);
}

int	redirect_in_mini(t_redir *rc, t_com *com, t_enpv *declare)
{
	int	i;
	int	j;

	rc->my_in = 0;
	j = redir_help_in_mini_part_one(com);
	i = redir_help_in_mini_part_two(rc, com, declare);
	if (i == -1)
		return (1);
	if (com->flag_heredoc == 2)
		rc->my_in = open("/goinfre/jnappa/tmp", O_RDONLY, 0664);
	else if (com->flag_heredoc == 1)
		rc->my_in = open(com->out_file[i - 1], O_RDONLY);
	return (0);
}

int	redirect_out_mini(t_redir *rc, t_com *com, t_enpv *declare)
{
	int	i;
	int	j;

	rc->my_out = 0;
	if (com->flag == 0)
		return (0);
	i = redir_out_mini_part_one(rc, com, declare);
	if (i == -1)
		return (1);
	j = redir_out_mini_part_two(rc, com, declare);
	if (j == -1)
		return (1);
	if (com->flag == 2)
		rc->my_out = open(com->in_in_file[j - 1], O_WRONLY | O_APPEND);
	else
		rc->my_out = open(com->in_file[i - 1], O_WRONLY | O_TRUNC);
	return (0);
}

void	redirect_main(t_redir *redir, t_com *com, t_enpv *declare)
{
	if (redirect_out_mini(redir, com, declare))
		return ;
	if (redirect_in_mini(redir, com, declare))
		return ;
}
