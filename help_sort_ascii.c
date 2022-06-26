/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sort_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:52:48 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 22:52:50 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_cmp_normal(char *str_one, char *str_two)
{
	int	i;

	i = 0;
	while (str_one[i] || str_two[i])
	{
		if (str_one[i] != str_two[i])
			return (str_one[i] - str_two[i]);
		i++;
	}
	return (0);
}

int	found_in_array(int count, char *str, char **array)
{
	int	i;

	i = 0;
	count--;
	while (count >= 0)
	{
		if (!ft_cmp_normal(array[count], str))
			return (1);
		count--;
	}
	return (0);
}

void	help_sort_ascii(char **max, t_enpv *next, char **arr, int y)
{
	if (!found_in_array(y, next->name, arr))
	{
		if (*max == NULL)
			*max = next->name;
		else if (ft_cmp_normal(*max, next->name) > 0)
			*max = next->name;
	}
}
