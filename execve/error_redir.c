/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:58:06 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 19:05:04 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_no_file(char *file_name, t_enpv *declare)
{
	t_enpv	*temp;

	fd_putstr("minishell: ", 2);
	fd_putstr(file_name, 2);
	fd_putstr(": No such file or directory\n", 2);
	temp = get_adress_info(declare, "?");
	free(temp->info);
	temp->info = copy_str("1", 0, 1);
	return ;
}

void	error_permisson_denaid(char *file_name, t_enpv *declare)
{
	t_enpv	*temp;

	fd_putstr("minishell: ", 2);
	fd_putstr(file_name, 2);
	fd_putstr(" : Permission denied\n", 2);
	temp = get_adress_info(declare, "?");
	free(temp->info);
	temp->info = copy_str("1", 0, 1);
	return ;
}
