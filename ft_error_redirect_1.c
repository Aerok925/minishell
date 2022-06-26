/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redirect_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:51:35 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:51:41 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_marker_redirect(char *s, int *i, char c)
{
	int	count;

	count = 1;
	while (s[++(*i)])
	{
		if (s[*i] == c)
			count++;
		if (s[*i] != c)
			break ;
	}
	return (count);
}

char	*ft_found_error_red(char *s, int *i, char c)
{
	while (s[*i])
	{
		if (s[*i] != c)
			break ;
		(*i)++;
	}
	while (s[*i])
	{
		if (s[*i] != '\f')
			break ;
		(*i)++;
	}
	if (s[*i] == '\0')
		return ("newline");
	if (s[*i] == '<')
		return ("<");
	if (s[*i] == '>')
		return (">");
	return (NULL);
}
