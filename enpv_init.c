/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enpv_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:45:00 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 19:21:15 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ищем первый знак =
static int	found_first_equall(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

//копия строки начиная с опледеленного символа и заканчивая другим символом
char	*copy_str(char *str, int begin, int end)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(end - begin + 1);
	if (!new_str)
		return (NULL);
	while (i + begin < end)
	{
		new_str[i] = str[i + begin];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

//создание нового елемента листа
static t_enpv	*new_elem_lst(char *str)
{
	t_enpv	*new;

	new = malloc(sizeof(t_enpv));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->name = copy_str(str, 0, found_first_equall(str));
	new->info = copy_str(str, found_first_equall(str) + 1, ft_strlen(str));
	new->exp = 1;
	return (new);
}

t_enpv	*enpv_init(char **enpv)
{
	int		i;
	t_enpv	*my_enpv;
	t_enpv	*next;

	i = 0;
	my_enpv = NULL;
	while (enpv[i])
	{
		if (my_enpv == NULL)
		{
			my_enpv = new_elem_lst(enpv[i]);
			next = my_enpv;
		}
		else
		{
			next->next = new_elem_lst(enpv[i]);
			next = next->next;
		}
		i++;
	}
	init_shlvl(my_enpv);
	init_pwd(my_enpv);
	init_old_pwd(my_enpv);
	init_last_command(my_enpv);
	return (my_enpv);
}
