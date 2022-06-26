/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_old_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:56:32 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:56:32 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_old_pwd(t_enpv *ls)
{
	t_enpv	*next;
	t_enpv	*new;

	next = ls;
	if (ft_get_info(next, "OLDPWD"))
		return ;
	new = malloc(sizeof(t_enpv));
	if (!new)
		return ;
	while (next->next)
		next = next->next;
	next->next = new;
	new->next = NULL;
	new->info = NULL;
	new->name = copy_str("OLDPWD", 0, 7);
	new->exp = 1;
}
