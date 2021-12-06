/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:05:23 by rpereda-          #+#    #+#             */
/*   Updated: 2021/12/06 18:11:22 by rpereda-         ###   ########.fr       */
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

char	*extract_line(char *rem)
{
	char	*line;
	size_t	i;

	if (!rem)
		return (NULL);
	i = linelen(rem);
	line = ft_substr(rem, 0, i + 1);
	return (line);
}

char	*extract_rem(char *rem)
{
	char	*line;
	size_t	i;

	if (!rem)
		return (NULL);
	i = linelen(rem);
	line = ft_substr(rem, i + 1, ft_strlen(rem) - i);
	free(rem);
	return (line);
}

char	*alloc_line(int fd, char *rem)
{
	char	*buffer;
	int		r_bytes;

	if (!rem)
		rem = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r_bytes = 1;
	while (!ft_strchr(rem, '\n') && r_bytes)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!*buffer || r_bytes == -1)
		{
			free(rem);
			free(buffer);
			return (NULL);
		}	
		buffer[r_bytes] = 0;
		rem = ft_strjoin(rem, buffer);
	}
	free(buffer);
	return (rem);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rem;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rem = alloc_line(fd, rem);
	if (!rem)
		return (NULL);
	if (!*rem)
		free(rem);
	line = extract_line(rem);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	rem = extract_rem(rem);
	return (line);
}
