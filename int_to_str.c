/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:38:42 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 16:35:23 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*int_to_str(int number)
{
	int		cp_number;
	char	*str;
	int		i;

	i = 0;
	if (number == 0)
	{
		str = copy_str("0", 0, 1);
		return (str);
	}
	cp_number = number;
	while (cp_number != 0)
	{
		cp_number /= 10;
		i++;
	}
	str = malloc(i + 1);
	str[i--] = '\0';
	while (number != 0)
	{
		str[i--] = number % 10 + '0';
		number /= 10;
	}
	return (str);
}
