/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:44 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:45 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_while_redirect(char *line, int *i)
{
	while (line[++(*i)])
	{
		if (line[*i] == '\f' || line[*i] == '\0' || line[*i] == '\n'
			|| line[*i] == '<' || line[*i] == '>')
			break ;
	}
}

char	*ft_redirect_out(t_com **com, char *line, int *i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = (*i);
	while (line[*i] == '<' || line[*i] == '\f')
		(*i)++;
	k = (*i);
	ft_while_redirect(line, i);
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, k, *i - k);
	ft_add_file(com, tmp2, 0);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	(*i) = ft_strlen(tmp) - 1;
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(line);
	return (tmp);
}

char	*ft_redirect_in(t_com **com, char *line, int *i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = (*i);
	while (line[*i] == '>' || line[*i] == '\f')
		(*i)++;
	k = (*i);
	ft_while_redirect(line, i);
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, k, *i - k);
	ft_add_file(com, tmp2, 1);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	(*i) = ft_strlen(tmp) - 1;
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(line);
	return (tmp);
}

char	*ft_redirect_in_in(t_com **com, char *line, int *i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = (*i);
	while (line[*i] == '>' || line[*i] == '\f')
		(*i)++;
	k = (*i);
	ft_while_redirect(line, i);
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, k, *i - k);
	ft_add_file(com, tmp2, 2);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	(*i) = ft_strlen(tmp) - 1;
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(line);
	return (tmp);
}

char	*ft_pars_redirect(t_mini **mini, t_com **com, char *str)
{
	int		i;
	char	*redirect;

	i = -1;
	redirect = ft_error_redirect(str, -1);
	while (str[++i] && redirect == NULL)
	{
		(*mini)->quote = ft_open_quote(str, str[i], i, (*mini)->quote);
		if (str[i] == '>' && str[i + 1] == '>' && (*mini)->quote == 0)
			str = ft_redirect_in_in(com, str, &i);
		if (str[i] == '>' && (*mini)->quote == 0)
			str = ft_redirect_in(com, str, &i);
		if (str[i] == '<' && str[i + 1] == '<' && (*mini)->quote == 0)
			str = ft_redirect_heredoc(com, str, &i);
		if (str[i] == '<' && (*mini)->quote == 0)
			str = ft_redirect_out(com, str, &i);
	}
	if (redirect)
	{
		free(str);
		return (ft_print_error_redirect(redirect));
	}
	return (str);
}
