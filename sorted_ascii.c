/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_ascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:35:03 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/01 16:56:38 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_digit(t_enpv *lst)
{
	t_enpv	*next;
	int		i;

	i = 0;
	next = lst;
	while (next)
	{
		if (next->exp == 1)
			i++;
		next = next->next;
	}
	return (i);
}

char	**exec_export_out(t_enpv *lst)
{
	char	**arr;
	int		i;
	char	*max;
	t_enpv	*next;
	int		y;

	i = number_of_digit(lst);
	arr = malloc(sizeof(char *) * (i + 1));
	y = 0;
	while (i > 0)
	{
		next = lst;
		max = NULL;
		while (next)
		{
			help_sort_ascii(&max, next, arr, y);
			next = next->next;
			if (next && next->exp == 0)
				next = next->next;
		}
		arr[y++] = max;
		i--;
	}
	arr[y] = NULL;
	return (arr);
}

void	out_export_lst(t_enpv *lst)
{
	char	**arr;
	int		i;
	t_enpv	*next;

	arr = exec_export_out(lst);
	i = 0;
	while (arr[i])
	{
		next = get_adress_info(lst, arr[i]);
		if (next->info)
			printf("declare -x %s=\"%s\"\n", next->name, next->info);
		else
			printf("declare -x %s=\"\"\n", next->name);
		i++;
	}
	free(arr);
}
