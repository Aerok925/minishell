/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:11 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:12 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_while_quot_2(t_enpv **env, t_enpv **my_envp, char *line, int *i)
{
	while (line[++(*i)])
	{
		if (line[*i] == '\"')
			break ;
		if (line[*i] == '\\' && (line[*i + 1] == '"'
				|| line[*i + 1] == '$' || line[*i + 1] == '\\'))
			line = ft_pars_slesh(line, i);
		if (line[*i] == '$')
			line = ft_pars_dollar(env, my_envp, line, i);
	}
	return (line);
}

char	*ft_pars_quote_1(char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (line[++(*i)])
		if (line[*i] == '\'')
			break ;
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp3 = ft_substr(line, *i + 1, ft_strlen(line));
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	(*i) -= 2;
	free(line);
	return (tmp);
}

char	*ft_pars_quote_2(t_enpv **env, t_enpv **my_envp, char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	line = ft_while_quot_2(env, my_envp, line, i);
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	(*i) -= 2;
	free(line);
	return (tmp);
}
