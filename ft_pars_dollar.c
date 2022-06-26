/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:02 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:04 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_while_env(t_enpv **env, t_enpv **my_envp, char *tmp, char *tmp2)
{
	t_enpv	*env_tmp;

	env_tmp = get_adress_info((*my_envp), tmp2);
	if (env_tmp)
		tmp = ft_strjoin(tmp, env_tmp->info);
	else
	{
		env_tmp = get_adress_info((*env), tmp2);
		if (env_tmp)
			if (env_tmp->info)
				tmp = ft_strjoin(tmp, env_tmp->info);
	}
	free(tmp2);
	return (tmp);
}

char	*ft_pars_dollar(t_enpv **env, t_enpv **my_envp, char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (line[++(*i)])
		if (!ft_key(line[*i]))
			break ;
	if (*i == j + 1)
		return (line);
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	tmp = ft_while_env(env, my_envp, tmp, tmp2);
	(*i) = ft_strlen(tmp) - 1;
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(line);
	return (tmp);
}
