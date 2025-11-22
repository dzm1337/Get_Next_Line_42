/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-paul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:54:25 by dde-paul          #+#    #+#             */
/*   Updated: 2025/11/22 15:32:44 by dde-paul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_line(char *stash, int fd) 
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int	nbytes;

	if (!stash)
		stash = ft_strdup("");
	while (!ft_strchr(stash, '\n'))
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes <= -1)
		{
			if (nbytes <= -1 || *stash == 0 || !stash)
				return (free(stash), NULL);
			return (stash);
		}
		buf[nbytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		if (!tmp)
			return (NULL);
		free(stash);
		stash = tmp;
	}
	return (stash);
}

char	*ft_get_line(char *stash)
{
	int	i;
	int	j;
	char	*line;
	
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_strdup(stash);
	return (free(stash), line);
}
char	*ft_delimit_line(char *stash)
{
	int	i;
	char	*tmp_stash;
	
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (NULL);
	i++;
	tmp_stash = ft_strdup(stash + i);
	if (!tmp_stash)
		return (NULL);
	return (free(stash), tmp_stash);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char	*line;

	stash = ft_read_line(stash, fd);
	if (!stash || stash[0] == '\0' || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_delimit_line(stash);

	return (line);
}
