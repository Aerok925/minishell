/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:14:16 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/31 18:16:40 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_command(t_com *lst)
{
	t_com	*com;

	while (lst)
	{
		com = lst;
		free(lst->options);
		free(lst->command);
		free_arr(lst->arg);
		free(lst->line);
		free_arr(lst->in_file);
		free_arr(lst->in_in_file);
		free_arr(lst->out_file);
		free_arr(lst->heredoc);
		lst = lst->next;
		free(com);
	}
}
