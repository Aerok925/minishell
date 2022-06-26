/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:29:39 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 22:29:40 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_shlvl(int number, t_enpv *shlvl_lst)
{
	if (number == 0)
	{
		shlvl_lst->info = copy_str("1", 0, 1);
		return (1);
	}
	if (number == -1)
	{
		shlvl_lst->info = copy_str("0", 0, 1);
		return (1);
	}
	if (++number == 1000)
	{
		shlvl_lst->info = NULL;
		return (1);
	}
	return (0);
}
