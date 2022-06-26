/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:51:31 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:51:32 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_heredoc(char *error, char *str)
{
	printf("%s (wanted '%s')\n", error, str);
}

char	*ft_redirect_heredoc(t_com **com, char *line, int *i)
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
	ft_add_file(com, tmp2, 3);
	tmp3 = ft_substr(line, *i, ft_strlen(line));
	(*i) = ft_strlen(tmp) - 1;
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(line);
	return (tmp);
}

void	ft_heredoc(char *name)
{
	char	*buf;
	char	*line;
	int		fd;

	line = ft_strdup("");
	g_kost = 1;
	while (1337)
	{
		buf = readline("> ");
		if (!buf || g_kost == 0 || ft_strcmp(buf, name) == 0)
		{
			if (!buf)
				ft_error_heredoc(ERR_CTRL_D, name);
			break ;
		}
		line = ft_strjoin(line, buf);
		line = ft_strjoin(line, "\n");
		free(buf);
	}
	g_kost = 0;
	free(buf);
	fd = open("/goinfre/jnappa/tmp", O_C | O_T | O_W, 0664);
	write(fd, line, ft_strlen(line));
	free(line);
	close(fd);
}
