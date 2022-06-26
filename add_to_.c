/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:31:46 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 20:07:35 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_declare(char *str, t_enpv *declare)
{
	t_enpv	*temp;

	temp = get_adress_info(declare, "_");
	free(temp->info);
	if (str == NULL)
		temp->info = copy_str("=", 0, 1);
	else
		temp->info = copy_str(str, 0, ft_strlen(str));
}

static void	add_to_part(t_enpv *declare, t_com *command)
{
	int		i;
	char	**opt;

	i = 0;
	if (command->options)
	{
		opt = ft_split(command->options, '\n');
		while (opt[i])
			i++;
		add_declare(opt[i - 1], declare);
		free_arr(opt);
	}
	else if (command->command)
		add_declare(command->command, declare);
}

void	add_to_(t_enpv *declare, t_com *command)
{
	int		i;
	char	**opt;

	i = 0;
	if (ft_cmp(command->command, "export") && command->arg)
	{
		while (command->arg[i])
			i++;
		opt = ft_split(command->arg[i - 1], '=');
		add_declare(opt[0], declare);
		free_arr(opt);
	}
	else if (command->arg)
	{
		while (command->arg[i])
			i++;
		add_declare(command->arg[i - 1], declare);
	}
	else
		add_to_part(declare, command);
}
