/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_slesh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:53:18 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:53:19 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pars_slesh(char *line, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, 0, *i);
	tmp2 = ft_substr(line, *i + 1, ft_strlen(line));
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(line);
	return (tmp);
}
