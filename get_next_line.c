#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
size_t	linelen(char *s)
{
	size_t	i;

	i = 0;
	while(s[i] != '\n' && s[i])
		i++;
	return(i);
}
char	*extract_line(char *rem)
{
	char	*line;
	size_t	i;

	i = linelen(rem);
	line = ft_substr(rem, 0, i + 1);
	return(line);
}
char	*extract_rem(char *rem)
{
	char	*line;
	size_t	i;

	i = linelen(rem);
	line = ft_substr(rem, i + 1, ft_strlen(rem) - i);
	free(rem);
	return (line);
}
char	*alloc_line(int fd, char *rem)	
{
	char	*buffer;
	int		r_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buffer)
		return (NULL);
	r_bytes = 1;
	if(!rem)
		rem = ft_strdup("");
	while(!ft_strchr(rem,'\n') && r_bytes)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
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
		return(NULL);
	rem = alloc_line(fd, rem);
	if(!rem)
		return (NULL);
	line = extract_line(rem);
	rem = extract_rem(rem);
	printf("%s",line);
	return(line);
}

/* Read recuerda la posición del archivo en la que estaba en cada llamada, por lo que
puedo leer, después comprobar si en el buffer está \n, si es así devolver hasta ahí y guardar
el restante de lo leído (si lo hay) a rem (¿Qué pasa si leo todo de golpe?); si no es así  guardo buff en un auxiliar en el heap,
añadiendole un \0 en la última posición (¿Usar memmove o strdup?) sigo leyendo y cada vez que lea hago strjoin y compruebo si hay un \n, liberando
el aux ya que tengo mis cositas en el string de strdup. AAA XDDDDDD
Hacer esto sucesivamente hasta EOF.
*/