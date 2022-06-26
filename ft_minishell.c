/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:51:54 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:51:56 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_mini(t_mini *mini)
{
	free_lst_command(mini->com);
	free(mini);
}

static void	ctrl_d(t_mini *mini, t_enpv *my_enpv, t_enpv *declare)
{
	ft_error("exit\n");
	ft_free_mini(mini);
	free_lst(declare);
	free_lst(my_enpv);
}

void	ft_minishell(t_enpv **my_envp, t_enpv **decl)
{
	t_mini	*mini;
	char	*line;

	while (1337)
	{
		line = readline("minishell$ ");
		shell_init(&mini);
		if (!line)
		{
			ctrl_d(mini, *my_envp, *decl);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0)
			ft_pre_parsing(&mini, my_envp, decl, line);
		*my_envp = distribution_command(*my_envp, mini, *decl, line);
		free(line);
		ft_free_mini(mini);
	}
}
