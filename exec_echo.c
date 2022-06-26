/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:41:02 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/04 00:41:04 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_no_option(t_com *com)
{
	int	i;

	if (com->arg == NULL)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while (com->arg[i])
		printf("%s ", com->arg[i++]);
	printf("\n");
}

void	echo_option(t_com *com)
{
	int	i;

	if (com->arg == NULL)
		return ;
	i = 0;
	while (com->arg[i])
		printf("%s", com->arg[i++]);
}

void	exec_echo(t_com *com, t_enpv *declare)
{
	int		i;
	char	**arr;
	int		flag;

	i = 0;
	flag = 0;
	if (com->options)
		arr = ft_split(com->options, '\n');
	else
		arr = NULL;
	while (arr && arr[i])
	{
		if (ft_strcmp("-n", arr[i]) == 0)
		{
			echo_option(com);
			flag = 1;
			break ;
		}
		i++;
	}
	free_arr(arr);
	if (!flag)
		echo_no_option(com);
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(0);
}
