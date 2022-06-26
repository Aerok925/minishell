/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_help_in_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:07:53 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 19:07:54 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_out_mini_part_two(t_redir *rc, t_com *com, t_enpv *declare)
{
	int	j;
	int	fd;

	j = 0;
	if (com->in_in_file)
	{
		while (com->in_in_file[j])
		{
			fd = open(com->in_in_file[j], O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fd > 0)
				close(fd);
			else
			{
				error_permisson_denaid(com->in_in_file[j], declare);
				rc->my_out = -1;
				return (-1);
			}
			j++;
		}
	}
	return (j);
}

int	redir_out_mini_part_one(t_redir *rc, t_com *com, t_enpv *declare)
{
	int	i;
	int	fd;

	i = 0;
	if (com->in_file)
	{
		while (com->in_file[i])
		{
			fd = open(com->in_file[i], O_CREAT | O_WRONLY | O_TRUNC, 0664);
			if (fd > 0)
				close(fd);
			else
			{
				error_permisson_denaid(com->in_file[i], declare);
				rc->my_out = -1;
				return (-1);
			}
			i++;
		}
	}
	return (i);
}
