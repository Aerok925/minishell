/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:49:52 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:49:59 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_option(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (i > 0)
			if (line[1][0] == '-')
				return (1);
	}
	return (0);
}

static void	ft_option(t_com **com, char **line, int *i)
{
	while (line[*i] && line[++(*i)])
	{
		if ((*i) > 0)
		{
			if (line[*i][0] == '-' && ft_strlen(line[*i]) > 1)
			{
				(*com)->options = ft_strjoin((*com)->options, line[*i]);
				(*com)->options = ft_strjoin((*com)->options, "\n");
			}
			else
			{
				while (line[*i])
				{
					if (ft_strlen(line[*i]) > 0)
					(*com)->arg = add_str_in_arr((*com)->arg, line[*i]);
					(*i)++;
				}
				break ;
			}
		}
	}
}

void	ft_add_commands(t_com **com, char **line)
{
	int	i;

	if (ft_check_option(line))
		(*com)->options = ft_strdup("");
	i = 0;
	while (ft_strcmp(line[i], "") == 0)
		i++;
	if (line[i])
		(*com)->command = ft_strdup(line[i]);
	ft_option(com, line, &i);
}

//static void	ft_add_fd(t_com **com)
//{
//	if ((*com)->flag == 1)
//		ft_open_in(com);
//	if ((*com)->flag == 2)
//		ft_open_in_in(com);
//	if ((*com)->flag == 3)
//		ft_open_out(com);
//}

void	ft_pars_files(t_enpv **env, t_enpv **decl, t_com **com)
{
	t_com	*tmp;
	int		i;

	tmp = (*com);
	while (tmp != NULL)
	{
		i = -1;
		if (tmp->in_in_file)
			while (tmp->in_in_file[++i])
				tmp->in_in_file[i] = ft_parsing(env, decl, tmp->in_in_file[i]);
		i = -1;
		if (tmp->in_file)
			while (tmp->in_file[++i])
				tmp->in_file[i] = ft_parsing(env, decl, tmp->in_file[i]);
		i = -1;
		if (tmp->out_file)
			while (tmp->out_file[++i])
				tmp->out_file[i] = ft_parsing(env, decl, tmp->out_file[i]);
		i = -1;
		if (tmp->heredoc)
			while (tmp->heredoc[++i])
				tmp->heredoc[i] = ft_parsing(env, decl, tmp->heredoc[i]);
		tmp = tmp->next;
	}
}
