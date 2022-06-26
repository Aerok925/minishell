/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:52:46 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:52:47 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_in(t_com **com)
{
	int	i;

	i = -1;
	while ((*com)->in_file[++i])
	{
		if ((*com)->fd_in)
			close((*com)->fd_in);
		(*com)->fd_in = open((*com)->in_file[i], O_W | O_C | O_T, 0644);
	}
}

void	ft_open_in_in(t_com **com)
{
	int	i;

	i = -1;
	while ((*com)->in_in_file[++i])
	{
		if ((*com)->fd_in)
			close((*com)->fd_in);
		(*com)->fd_in = open((*com)->in_in_file[i], O_W | O_C | O_A, 0644);
	}
}

void	ft_open_out(t_com **com)
{
	int	i;

	i = -1;
	while ((*com)->out_file[++i])
	{
		if ((*com)->fd_in)
			close((*com)->fd_in);
		(*com)->fd_in = open((*com)->out_file[i], O_R, 0644);
	}
}
