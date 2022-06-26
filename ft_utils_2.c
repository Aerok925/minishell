/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:55:35 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 21:55:39 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	*ft_strstr(char *big, char *little)
{
	size_t	i;
	size_t	u;
	size_t	temp_i;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i])
	{
		u = 0;
		if (big[i] == little[u])
		{
			temp_i = i;
			while (big[temp_i] == little[u])
			{
				u++;
				temp_i++;
				if (little[u] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (n == 0 || d == s)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	len;

	if (s != NULL)
	{
		len = ft_strlen(s);
		str = (char *) malloc(len + 1);
		if (str)
		{
			ft_memcpy(str, s, len);
			str[len] = '\0';
			return (str);
		}
	}
	return (NULL);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + 2);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[++i] = '\0';
	free(s1);
	return (str);
}
