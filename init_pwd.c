/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:56:55 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:56:56 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pwd(t_enpv *lst)
{
	t_enpv	*next;
	t_enpv	*new;

	next = lst;
	if (ft_get_info(lst, "PWD"))
	{
		next = get_adress_info(lst, "PWD");
		free(next->info);
		next->info = getcwd(NULL, 0);
		return ;
	}
	while (next->next)
		next = next->next;
	new = malloc(sizeof(t_enpv));
	if (!new)
		return ;
	new->name = copy_str("PWD", 0, 3);
	new->info = getcwd(NULL, 0);
	new->next = NULL;
	next->next = new;
	new->exp = 1;
}
