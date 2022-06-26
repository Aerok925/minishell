/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:53 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:54 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error_pipe(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(line, ISSPACE);
	while (str[i])
		i++;
	if (str[i - 1] == '|' || str[0] == '|')
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

static char	*ft_while_pipe(t_mini **mini, char *line, char c)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		(*mini)->quote = ft_open_quote(line, line[i], i, (*mini)->quote);
		if (line[i] == c && (*mini)->quote == 0)
			line[i] = '\f';
	}
	return (line);
}

static void	ft_after_pipe(t_mini **mini, t_com **com, t_enpv **e, t_enpv **d)
{
	int		i;
	char	**str;

	(*com)->line = ft_while_pipe(mini, (*com)->line, ' ');
	if (ft_strlen((*com)->line) > 0)
	{
		(*com)->line = ft_pars_redirect(mini, com, (*com)->line);
		ft_pars_files(e, d, com);
		if ((*com)->line != NULL)
		{
			str = ft_split((*com)->line, '\f');
			i = -1;
			while (str != NULL && str[++i])
				str[i] = ft_parsing(e, d, str[i]);
			ft_add_commands(com, str);
			free_arr(str);
		}
	}
}

static int	ft_delete_pipe(t_mini **mini, char *line)
{
	int		i;
	char	**str;

	if (ft_error_pipe(line))
	{
		line = ft_while_pipe(mini, line, '|');
		if ((*mini)->quote != 0)
			return (ft_error(ERR_QUOTES));
		if (ft_strlen(line) > 0)
		{
			str = ft_split(line, '\f');
			i = 0;
			(*mini)->com->line = ft_strdup(str[i]);
			while (str[++i])
				ft_add_next(&(*mini)->com, ft_strtrim(str[i], ISSPACE), i);
			free_arr(str);
			return (1);
		}
		return (0);
	}
	else
		return (ft_error(ERR_PIPE));
}

void	ft_pre_parsing(t_mini **mini, t_enpv **env, t_enpv **decl, char *line)
{
	t_com	*temp;
	char	*tmp;

	tmp = ft_strtrim(line, ISSPACE);
	if (ft_delete_pipe(mini, tmp) != 0)
	{
		temp = (*mini)->com;
		while (temp != NULL)
		{
			if (temp->line != NULL)
				ft_after_pipe(mini, &temp, env, decl);
			temp = temp->next;
		}
	}
	free(tmp);
}
