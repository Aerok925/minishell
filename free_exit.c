/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:43:07 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 20:43:08 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exit_help(t_com *command)
{
	char	**arg;

	if (command->options)
		arg = ft_split(command->options, '\n');
	if (command->arg && command->options)
		arg = add_to_array(arg, command->arg);
	else if (command->arg)
		arg = copy_arr(command->arg);
	return (arg);
}

void	free_exit(t_enpv *my_envp, t_enpv *declare, char *line, t_mini *mini)
{
	fd_putstr("exit\n", 2);
	free_lst(my_envp);
	free_lst(declare);
	free_lst_command(mini->com);
	free(mini);
	free(line);
}
