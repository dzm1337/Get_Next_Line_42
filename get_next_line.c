/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-paul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:54:25 by dde-paul          #+#    #+#             */
/*   Updated: 2025/11/16 19:54:22 by dde-paul         ###   ########.fr       */
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
	nbytes = 1;
	while (!ft_strchr(stash, '\n') && nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[nbytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		free(stash);
		stash = tmp;
	}
	return (stash);
}
char	*ft_delimit_line(char *stash)
{
	int	i;
	int	j;
	char	*tmp_stash;
	
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i = i + 1;
	tmp_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!tmp_stash)
		return (NULL);
	j = i;
	i = 0;
	while (stash[j])
	{
		tmp_stash[i] = stash[j];
		i++;
		j++;
	}
	tmp_stash[i] = '\0';
	free(stash);
	stash = tmp_stash;
	return (stash);
}
/*
char	*ft_get_line(char *stash)
{
}	
char	*ft_get_next_line(int fd)
{
}
*/

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h> 

int main(void)
{
    int fd;
    char *line;

    fd = open("teste.txt", O);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    line = ft_read_line(NULL, fd);
    if (line)
    {
        printf("Linha lida: %s\n", line);
        free(line);
    }
    else
    {
        printf("Erro ao ler a linha ou arquivo vazio.\n");
    }
    close(fd);
    return 0;
}

