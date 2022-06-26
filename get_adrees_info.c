/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_adrees_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:14:15 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/28 20:16:46 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enpv	*get_adress_info(t_enpv *lst, char *str)
{
	t_enpv	*next;

	next = lst;
	while (next)
	{
		if (ft_cmp(next->name, str))
			return (next);
		next = next->next;
	}
	return (NULL);
}
