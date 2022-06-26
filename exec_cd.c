/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:06:36 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/03 23:33:12 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_daclare(char *str, t_enpv *declare)
{
	t_enpv	*temp;

	temp = get_adress_info(declare, "?");
	free(temp->info);
	temp->info = copy_str(str, 0, ft_strlen(str));
}

void	branch_pwd(char *old_pwd, t_enpv *lst, t_enpv *declare)
{
	t_enpv	*temp;

	if (get_adress_info(lst, "PWD") && get_adress_info(lst, "OLDPWD"))
	{
		temp = get_adress_info(lst, "OLDPWD");
		free(temp->info);
		temp->info = get_adress_info(lst, "PWD")->info;
		temp = get_adress_info(lst, "PWD");
		temp->info = getcwd(NULL, 0);
		free(old_pwd);
	}
	else if (get_adress_info(lst, "PWD"))
	{
		temp = get_adress_info(lst, "PWD");
		free(temp->info);
		temp->info = getcwd(NULL, 0);
		free(old_pwd);
	}
	else
	{
		temp = get_adress_info(lst, "OLDPWD");
		free(temp->info);
		temp->info = old_pwd;
	}
	add_daclare("0", declare);
}

void	exec_cd(t_enpv *lst, t_enpv *declare, t_com *command)
{
	char	*str;
	char	*old_pwd;

	if (command->arg)
		str = command->arg[0];
	else if (get_adress_info(lst, "HOME") != NULL)
		str = get_adress_info(lst, "HOME")->info;
	else
	{
		add_daclare("1", declare);
		fd_putstr("minishell: cd: HOME not set\n", 2);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(str) == 0)
		branch_pwd(old_pwd, lst, declare);
	else
	{
		free(old_pwd);
		perror("minishell");
		add_daclare("1", declare);
	}
}
