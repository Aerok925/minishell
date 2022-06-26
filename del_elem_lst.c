/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_elem_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:51:40 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/01 23:21:59 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elem_lst(t_enpv *lst)
{
	free(lst->name);
	if (lst->info)
		free(lst->info);
	free(lst);
}

t_enpv	*del_elem_dop(t_enpv *lst, char *str)
{
	t_enpv	*begin;
	t_enpv	*next;

	next = lst;
	begin = lst;
	while (next)
	{
		if (ft_cmp(next->name, str))
		{
			begin->next = next->next;
			free_elem_lst(next);
			break ;
		}
		begin = next;
		next = next->next;
	}
	return (lst);
}

t_enpv	*del_elem_lst(t_enpv *lst, char *str)
{
	t_enpv	*begin;
	t_enpv	*next;

	if (str == NULL)
		return (lst);
	if (ft_cmp(lst->name, str))
	{
		begin = lst->next;
		next = lst;
		lst = lst->next;
		free_elem_lst(next);
		return (lst);
	}
	lst = del_elem_dop(lst, str);
	return (lst);
}
