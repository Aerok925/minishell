/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:09:12 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:54:08 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_con_three(char *str_one, char *str_two, char *str_three)
{
	char	*str_ret;
	int		i;
	int		y;

	y = 0;
	i = 0;
	str_ret = malloc(ft_strlen(str_one) + ft_strlen(str_two)
			+ ft_strlen(str_three) + 1);
	if (!str_ret)
		return (NULL);
	while (str_one[y])
		str_ret[i++] = str_one[y++];
	y = 0;
	while (str_two[y])
		str_ret[i++] = str_two[y++];
	y = 0;
	while (str_three[y])
		str_ret[i++] = str_three[y++];
	str_ret[i] = '\0';
	return (str_ret);
}
