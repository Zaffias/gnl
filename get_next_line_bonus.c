/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:10:14 by rpereda-          #+#    #+#             */
/*   Updated: 2021/12/06 16:33:22 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

size_t	linelen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	return (i);
}

char	*extract_line(char **rem, int fd)
{
	char	*line;
	size_t	i;

	if (!rem[fd])
		return (NULL);
	i = linelen(rem[fd]);
	line = ft_substr(rem[fd], 0, i + 1);
	return (line);
}

char	*extract_rem(char **rem, int fd)
{
	char	*line;
	size_t	i;

	if (!rem[fd])
		return (NULL);
	i = linelen(rem[fd]);
	line = ft_substr(rem[fd], i + 1, ft_strlen(rem[fd]) - i);
	free(rem[fd]);
	rem[fd] = NULL;
	return (line);
}

char	*alloc_line(int fd, char **rem)
{
	char	*buffer;
	int		r_bytes;

	if (!rem[fd])
		rem[fd] = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r_bytes = 1;
	while (!ft_strchr(rem[fd], '\n') && r_bytes)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!*buffer || r_bytes == -1)
		{
			free(rem[fd]);
			free(buffer);
			return (NULL);
		}	
		buffer[r_bytes] = 0;
		rem[fd] = ft_strjoin(rem[fd], buffer);
	}
	free(buffer);
	return (rem[fd]);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rem[5000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rem[fd] = alloc_line(fd, rem);
	if (!rem[fd])
		return (NULL);
	if (!*rem[fd])
		free(rem[fd]);
	line = extract_line(rem, fd);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	rem[fd] = extract_rem(rem, fd);
	if (!*rem)
	{
		free(rem[fd]);
		rem[fd] = NULL;
	}
	return (line);
}
