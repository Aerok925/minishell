/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:36:54 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 20:38:50 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_enpv *lst)
{
	t_enpv	*next;

	next = lst;
	while (next)
	{
		if (next->info)
			printf("%s=%s\n", next->name, next->info);
		next = next->next;
	}
}
