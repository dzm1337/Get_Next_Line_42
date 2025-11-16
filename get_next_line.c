/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-paul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:54:25 by dde-paul          #+#    #+#             */
/*   Updated: 2025/11/16 02:07:09 by dde-paul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_line(char *stash, int fd)
{
	char	temp_buf[BUFFER_SIZE + 1];
	int	nbytes;

	nbytes = 1; 
	while (ft_strchr(stash, '\n') && nbytes != 0)
	{
		nbytes = read(f. temp_buf, BUFFER_SIZE)
		temp_buf[nbytes] = '\0';
		ft_strjoin(stash, temp_buf);		
	}
	return (stash);
}

char	*ft_get_next_line(int fd)
{
	static char *stash;	
}
