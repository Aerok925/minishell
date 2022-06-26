/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst_enpv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:22:06 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 18:02:32 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_enpv *lst)
{
	t_enpv	*lst_tmp;

	while (lst)
	{
		lst_tmp = lst;
		free(lst_tmp->name);
		free(lst_tmp->info);
		lst = lst->next;
		free(lst_tmp);
	}
	lst = NULL;
}
