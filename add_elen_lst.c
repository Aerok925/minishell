/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elen_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:25:51 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 19:22:54 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_back(t_enpv *lst, char *name, char *info)
{
	t_enpv	*new;
	t_enpv	*next;

	new = malloc(sizeof(t_enpv));
	if (!new)
		return ;
	next = lst;
	while (next->next != NULL)
		next = next->next;
	if (name)
		new->name = copy_str(name, 0, ft_strlen(name));
	if (info)
		new->info = copy_str(info, 0, ft_strlen(info));
	else
		new->info = NULL;
	new->exp = 1;
	new->next = NULL;
	next->next = new;
}
