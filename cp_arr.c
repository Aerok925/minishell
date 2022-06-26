/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:19:22 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/01 22:20:06 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_array_char(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**copy_arr(char **arr)
{
	int		i;
	char	**cp_arr;

	cp_arr = malloc(sizeof(char *) * (size_of_array_char(arr) + 1));
	i = 0;
	while (arr[i])
	{
		cp_arr[i] = copy_str(arr[i], 0, ft_strlen(arr[i]));
		i++;
	}
	cp_arr[i] = NULL;
	return (cp_arr);
}
