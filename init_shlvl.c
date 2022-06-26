/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:33:13 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 18:20:33 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_enpv	*found_adress_lst(t_enpv *lst)
{
	t_enpv	*next;

	next = lst;
	while (next)
	{
		if (ft_cmp(next->name, "SHLVL"))
			return (next);
		next = next->next;
	}
	return (NULL);
}

static int	error_1000(int number)
{
	char	*str;

	fd_putstr("minishell: warning: shell level (", 2);
	str = int_to_str(number + 1);
	fd_putstr(str, 2);
	free(str);
	fd_putstr(") too high, resetting to 1\n", 2);
	return (0);
}

static int	ft_atoi(t_enpv *lst)
{
	t_enpv	*shlvl_lst;
	int		i;
	int		number;

	shlvl_lst = found_adress_lst(lst);
	i = 0;
	number = 0;
	if (shlvl_lst->info[i] == '-')
		i++;
	while (shlvl_lst->info[i])
	{
		if (shlvl_lst->info[i] >= '0' && shlvl_lst->info[i] <= '9')
			number = number * 10 + shlvl_lst->info[i] - 48;
		else
			return (0);
		i++;
	}
	if (number >= 1000)
		return (error_1000(number));
	if (shlvl_lst->info[0] == '-')
		return (-1);
	return (number);
}

static void	ft_itoa(t_enpv *lst, int number)
{
	t_enpv	*shlvl_lst;
	int		i;
	int		cp_number;

	shlvl_lst = found_adress_lst(lst);
	free(shlvl_lst->info);
	if (help_shlvl(number, shlvl_lst))
		return ;
	cp_number = number;
	i = 0;
	while (cp_number)
	{
		cp_number /= 10;
		i++;
	}
	shlvl_lst->info = malloc(i + 1);
	shlvl_lst->info[i--] = '\0';
	while (i >= 0)
	{
		shlvl_lst->info[i--] = number % 10 + 48;
		number = number / 10;
	}
}

void	init_shlvl(t_enpv *lst)
{
	t_enpv	*next;

	next = lst;
	if (ft_get_info(lst, "SHLVL") == NULL)
	{
		lst_add_back(lst, "SHLVL", "1");
		return ;
	}
	ft_itoa(lst, ft_atoi(lst));
}
