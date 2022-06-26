/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ready_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:50:21 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 15:50:59 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct_ready_command(t_ready_command *ready_command)
{
	free_arr(ready_command->env);
	free_arr(ready_command->options);
	free(ready_command->path_comand);
	free(ready_command);
}
