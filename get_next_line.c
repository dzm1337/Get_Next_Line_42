/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-paul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:54:25 by dde-paul          #+#    #+#             */
/*   Updated: 2025/11/29 17:23:27 by dde-paul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char *stash, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		nbytes;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	nbytes = 1;
	while (!ft_strchr(stash, '\n') && nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(stash), NULL);
		buf[nbytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		if (!tmp)
			return (free(stash), NULL);
		free(stash);
		stash = tmp;
	}
	return (stash);
}

char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;
	char	c;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	c = stash[i];
	stash[i] = '\0';
	line = ft_strdup(stash);
	if (!line)
		return (NULL);
	stash[i] = c;
	return (line);
}

char	*ft_delimit_line(char *stash)
{
	int		i;
	char	*tmp_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	tmp_stash = ft_strdup((stash + i) + 1);
	if (!tmp_stash)
		return (free(stash), NULL);
	if (!tmp_stash)
		return (NULL);
	free(stash);
	return (tmp_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_line(stash, fd);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_delimit_line(stash);
	return (line);
}
