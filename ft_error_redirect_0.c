/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redirect_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:51:02 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:51:08 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *error)
{
	write(1, error, ft_strlen(error));
	return (0);
}

char	*ft_print_error_redirect(char *line)
{
	printf("minishell: syntax error near unexpected marker ");
	printf("«%s»\n", line);
	return (NULL);
}

static int	ft_count_redirect(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '<')
		{
			count = ft_marker_redirect(s, &i, '<');
			if (count > 2)
				break ;
		}
		if (s[i] == '>')
		{
			count = ft_marker_redirect(s, &i, '>');
			if (count > 2)
				break ;
		}
	}
	return (count);
}

char	*ft_error_redirect(char *s, int i)
{
	int	count;

	count = ft_count_redirect(s);
	if (count == 3)
		return (">");
	if (count > 3)
		return (">>");
	while (s[++i])
	{
		if (s[i] == '>')
			if (ft_found_error_red(s, &i, '>'))
				return (ft_found_error_red(s, &i, '>'));
		if (s[i] == '<')
			if (ft_found_error_red(s, &i, '<'))
				return (ft_found_error_red(s, &i, '<'));
	}
	return (NULL);
}

void	ft_add_file(t_com **com, char *tmp, int k)
{
	if (k == 0)
	{
		(*com)->flag_heredoc = 1;
		(*com)->out_file = add_str_in_arr((*com)->out_file, tmp);
	}
	else if (k == 1)
	{
		(*com)->flag = 1;
		(*com)->in_file = add_str_in_arr((*com)->in_file, tmp);
	}
	else if (k == 2)
	{
		(*com)->flag = 2;
		(*com)->in_in_file = add_str_in_arr((*com)->in_in_file, tmp);
	}
	else if (k == 3)
	{
		(*com)->flag_heredoc = 2;
		(*com)->heredoc = add_str_in_arr((*com)->heredoc, tmp);
	}
	free(tmp);
}
