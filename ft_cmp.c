/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:17:16 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/30 18:32:59 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp(char *str_one, char *str_two)
{
	int	i;

	i = 0;
	if (ft_strlen(str_one) != ft_strlen(str_two))
		return (0);
	while (str_one[i])
	{
		if (str_one[i] != str_two[i])
			return (0);
		i++;
	}
	return (1);
}
