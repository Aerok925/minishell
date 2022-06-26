/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_info_in_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:13:25 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/30 18:33:00 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//получение любых данных из нашего ENPV
char	*ft_get_info(t_enpv *lst, char *found)
{
	t_enpv	*next;

	next = lst;
	while (next)
	{
		if (ft_cmp(next->name, found))
			return (next->info);
		next = next->next;
	}
	return (NULL);
}
