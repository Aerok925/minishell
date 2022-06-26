/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_last_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:26:38 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/29 18:27:55 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_last_command(t_enpv *lst)
{
	t_enpv	*next;

	next = get_adress_info(lst, "_");
	next->exp = 0;
}
