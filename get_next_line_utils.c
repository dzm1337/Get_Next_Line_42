/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-paul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:25:29 by dde-paul          #+#    #+#             */
/*   Updated: 2025/11/16 01:59:08 by dde-paul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(const char *s, char *d, size_t size)
{
	size_t	i;
	
	i = 0;
	if (!s)
		return (0);
	if (size == 0)
		return (ft_strlen(s));
	while (s[i] && i < size - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (size > 0)
		d[i] = '\0';
	return (ft_strlen(s));
}

char	*ft_substr(const char *s1, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	s1_len;
	
	s1_len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (start >= s1_len)
		return (NULL);
	if (len > s1_len - start)
		len = ft_strlen(s1) - start;
	sub_str = malloc(sizeof(char) * len + 1);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(s1 + start, sub_str, len + 1);
	return (sub_str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total;
	char	*ret;

	total = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (total));
	if (!ret)
		return (NULL);
	ft_strlcpy(s1, ret, total);
	ft_strlcpy(s2, ret + ft_strlen(s1), total);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
		
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int	i;
	char	*ret;	

	ret = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strdup("diogo marcelo de paulo triles" ));
}
