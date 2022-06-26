/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_for_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:45:01 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/02 17:12:18 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
		return (1);
	else
		i++;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '+' || str[i] == '-' || str[i] == '('
			|| str[i] == ')' || str[i] == '*' || str[i] == '%' || str[i] == '^'
			|| str[i] == '#' || str[i] == '@' || str[i] == '$' || str[i] == '!'
			|| str[i] == '~' || str[i] == '`' || str[i] == '.' || str[i] == ','
			|| str[i] == '/' || str[i] == '?' || str[i] == ' '
			|| str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

void	check_arg_for_unset(char **arr, t_enpv *declare)
{
	int		error;
	int		i;
	t_enpv	*temp;

	error = 0;
	i = 0;
	while (arr[i])
	{
		if (check_arg(arr[i]))
		{
			error = 1;
			fd_putstr("minishell: unset: `", 2);
			fd_putstr(arr[i], 2);
			fd_putstr("': not a valid identifier\n", 2);
			break ;
		}
		i++;
	}
	temp = get_adress_info(declare, "?");
	free(temp->info);
	if (error)
		temp->info = copy_str("1", 0, 1);
	else
		temp->info = copy_str("0", 0, 1);
}
