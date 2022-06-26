/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:52:28 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 20:12:23 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	first_char_in_str(char c, char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}

static char	**first_elem_in(t_ready_command *rd_com)
{
	int		i;
	char	**ret_value;

	i = 0;
	ret_value = malloc(sizeof(char *) * (2));
	ret_value[0] = copy_str(rd_com->path_comand, first_char_in_str('/',
				rd_com->path_comand) + 1, ft_strlen(rd_com->path_comand));
	ret_value[1] = NULL;
	return (ret_value);
}

void	create_options_for_command(t_com *com, t_ready_command *rd_com)
{
	char	**options;

	options = first_elem_in(rd_com);
	if (com->options)
		options = add_arr_in_arr(options, ft_split(com->options, '\n'));
	if (com->arg)
		options = add_arr_in_arr(options, copy_arr(com->arg));
	rd_com->options = options;
}
