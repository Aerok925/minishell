/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:23:06 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 16:47:08 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_enpv *declare)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("");
		free(get_adress_info(declare, "?")->info);
		get_adress_info(declare, "?")->info = int_to_str(errno);
		free(str);
		return ;
	}
	printf("%s\n", str);
	free(get_adress_info(declare, "?")->info);
	get_adress_info(declare, "?")->info = int_to_str(0);
	free(str);
}
