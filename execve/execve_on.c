/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_on.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:36:15 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/19 20:44:32 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	give_status(int *status)
{
	if (g_kost == 0)
		*status = 130;
	if (g_kost == 1)
		*status = 131;
	g_kost = 0;
}

void	execve_on(t_ready_command *rd_com, t_enpv *declare)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if (execve(rd_com->path_comand, rd_com->options, rd_com->env) == -1)
		{
			perror("execve");
			free_struct_ready_command(rd_com);
			exit(-1);
		}
	}
	else
	{
		wait(&status);
		free_struct_ready_command(rd_com);
		status /= 256;
		give_status(&status);
		free(get_adress_info(declare, "?")->info);
		get_adress_info(declare, "?")->info = int_to_str(status);
	}
}
