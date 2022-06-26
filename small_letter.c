/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_letter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:48:02 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/29 21:54:10 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	small_letter(t_com *com)
{
	int	i;

	i = 0;
	if (com->command == NULL)
		return ;
	while (com->command[i])
	{
		if (com->command[i] >= 65 && com->command[i] <= 90)
			com->command[i] += 32;
		i++;
	}
}
