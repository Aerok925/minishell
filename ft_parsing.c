/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:34 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:36 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_key(char c)
{
	return (c == '_' || c == '?' || ft_isalnum(c));
}

int	ft_open_quote(char *line, char c, int i, int flag)
{
	if (c == '\'' && i == 0 && flag == 0)
		return (1);
	else if (c == '\'' && line[i - 1] == '\\' && flag == 0)
		return (0);
	if (c == '\'' && flag == 0)
		return (1);
	if (c == '\'' && flag == 1)
		return (0);
	if (c == '"' && i == 0 && flag == 0)
		return (2);
	else if (c == '"' && line[i - 1] == '\\' && flag == 0)
		return (0);
	if (c == '"' && flag == 0)
		return (2);
	if (c == '"' && line[i - 1] == '\\' && flag == 2)
		return (2);
	else if (c == '"' && flag == 2)
		return (0);
	return (flag);
}

char	*ft_parsing(t_enpv **env, t_enpv **decl, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			line = ft_pars_quote_1(line, &i);
		else if (line[i] == '"')
			line = ft_pars_quote_2(env, decl, line, &i);
		else if (line[i] == '\\')
			line = ft_pars_slesh(line, &i);
		if (line[i] == '$')
			line = ft_pars_dollar(env, decl, line, &i);
	}
	return (line);
}
