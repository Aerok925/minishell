/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:31:10 by jnappa            #+#    #+#             */
/*   Updated: 2022/01/29 18:34:31 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	set_last_write(t_enpv *lst)
{
	t_enpv	*new;

	new = malloc(sizeof(t_enpv));
	if (!new)
		return ;
	new->name = copy_str("_", 0, ft_strlen("_"));
	new->info = copy_str("/Users/jnappa/minishell1/./minishell",
			0, ft_strlen("/Users/jnappa/minishell1/./minishell"));
	new->next = NULL;
	lst->next = new;
}

t_enpv	*init_declare(void)
{
	t_enpv	*new;

	new = malloc(sizeof(t_enpv));
	if (!new)
		return (NULL);
	new->name = copy_str("?", 0, ft_strlen("?"));
	new->info = copy_str("0", 0, ft_strlen("0"));
	new->next = NULL;
	set_last_write(new);
	return (new);
}
