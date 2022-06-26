/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:21:32 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 20:27:17 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_in_arr(t_enpv *env, t_ready_command *rd_com)
{
	char	**env_arr;
	t_enpv	*temp;
	char	*str;

	env_arr = malloc(sizeof(char *));
	env_arr[0] = NULL;
	temp = env;
	while (temp)
	{
		if (temp->info)
		{
			str = ft_str_con_three(temp->name, "=", temp->info);
			env_arr = add_str_in_arr(env_arr, str);
			free(str);
		}
		temp = temp->next;
	}
	rd_com->env = env_arr;
}
