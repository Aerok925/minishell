/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:31:31 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 21:13:38 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_in_two_str(char *str, char c)
{
	int		i;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	arr[0] = copy_str(str, 0, i);
	arr[1] = copy_str(str, i + 1, ft_strlen(str));
	arr[2] = NULL;
	return (arr);
}

static int	check_value(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
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

void	exec_branch_path(t_enpv *lst, char **arr, t_enpv *temp)
{
	if (get_adress_info(lst, arr[0]) == NULL)
	{
		if (arr[1][0])
			lst_add_back(lst, arr[0], arr[1]);
		else
			lst_add_back(lst, arr[0], NULL);
	}
	else if (arr[1][0] != 0)
	{
		temp = get_adress_info(lst, arr[0]);
		free(temp->info);
		temp->info = copy_str(arr[1], 0, ft_strlen(arr[1]));
	}
}

void	error_branch(int *error, int i, t_com *com)
{
	*error = 1;
	fd_putstr("minishell: export: `", 2);
	fd_putstr(com->arg[i], 2);
	fd_putstr("': not a valid identifier\n", 2);
}

void	exec_branch(t_enpv *lst, t_com	*com, t_enpv *declare)
{
	int		i;
	char	**arr;
	int		error;
	t_enpv	*temp;

	error = 0;
	i = 0;
	temp = NULL;
	if (com->arg == NULL)
		out_export_lst(lst);
	else
	{
		while (com->arg[i])
		{
			arr = split_in_two_str(com->arg[i], '=');
			if (!check_value(arr[0]))
				exec_branch_path(lst, arr, temp);
			else
				error_branch(&error, i, com);
			free_arr(arr);
			i++;
		}
	}
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(error);
}
