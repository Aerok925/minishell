/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arr_in_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:16:25 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 19:40:32 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arr_in_arr(char **arr, char **arr2)
{
	int		i;
	int		y;
	char	**ret_arr;

	i = 0;
	y = 0;
	ret_arr = malloc(sizeof(char *) * (arr_len(arr) + arr_len(arr2) + 1));
	while (arr[i])
	{
		ret_arr[i] = copy_str(arr[i], 0, ft_strlen(arr[i]));
		i++;
	}
	while (arr2[y])
	{
		ret_arr[i] = copy_str(arr2[y], 0, ft_strlen(arr2[y]));
		y++;
		i++;
	}
	ret_arr[i++] = NULL;
	free_arr(arr);
	free_arr(arr2);
	return (ret_arr);
}
