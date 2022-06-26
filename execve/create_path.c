/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:39:07 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 16:23:31 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_str_in_arr(char **arr, char *str)
{
	int		i;
	char	**ret_value;

	i = 0;
	if (!arr && !str)
		return (NULL);
	while (arr != NULL && arr[i])
		i++;
	ret_value = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr != NULL && arr[i])
	{
		ret_value[i] = copy_str(arr[i], 0, ft_strlen(arr[i]));
		i++;
	}
	ret_value[i++] = copy_str(str, 0, ft_strlen(str));
	ret_value[i] = NULL;
	free_arr(arr);
	return (ret_value);
}

static void	update_paths(char **paths, char *command)
{
	int		i;
	char	*str;

	i = 1;
	while (paths[i])
	{
		str = ft_str_con_three(paths[i], "/", command);
		free(paths[i]);
		paths[i++] = str;
	}
}

void	create_final_path(char **paths, t_ready_command *ready_com)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			ready_com->path_comand = copy_str(paths[i], 0, ft_strlen(paths[i]));
			free_arr(paths);
			return ;
		}
		i++;
	}
	free_arr(paths);
}

void	create_path(t_enpv *env, t_ready_command *ready_com, t_com *com)
{
	char	**paths;
	char	**path;
	int		i;

	i = 0;
	paths = malloc(sizeof(char *) * 2);
	paths[0] = copy_str(com->command, 0, ft_strlen(com->command));
	paths[1] = NULL;
	if (get_adress_info(env, "PATH"))
		path = ft_split(get_adress_info(env, "PATH")->info, ':');
	else
		path = NULL;
	while (path && path[i])
		paths = add_str_in_arr(paths, path[i++]);
	free_arr(path);
	update_paths(paths, com->command);
	create_final_path(paths, ready_com);
}
