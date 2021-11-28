#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
char	*line_read(char *raw_line, char **rem)
{
	size_t	i;
	char	*res;
	size_t	len;

	len = ft_strlen(raw_line);
	i = 0;
	while(raw_line[i] != '\n')
		i++;
	res = ft_substr(raw_line, 0, i + 1);
	*rem = ft_substr(raw_line, i, (len - i) - 3);
	return(res);
}
char	*get_next_line(int fd)
{
	ssize_t		bytes_rd;
	char		buffer[BUFFER_SIZE + 1];
	static char	**rem;
	char		*aux;
	char		*res;

	bytes_rd = 1;
	while(bytes_rd > 0)
	{
		bytes_rd = read(fd , buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = 0;
		if(!*rem)
			*rem = ft_strdup("");
		aux = ft_strjoin(*rem, buffer);
		if (ft_strchr(aux,'\n'))
			break;
	}
	res = line_read(aux, rem);
	printf("Primer salto de línea: %s\nResto del buffer%s", res, *rem);
}
int main()
{
	int fd = open("b",O_RDONLY);
	
	get_next_line(fd);
}
/* Read recuerda la posición del archivo en la que estaba en cada llamada, por lo que
puedo leer, después comprobar si en el buffer está \n, si es así devolver hasta ahí y guardar
el restante de lo leído (si lo hay) a rem (¿Qué pasa si leo todo de golpe?); si no es así  guardo buff en un auxiliar en el heap,
añadiendole un \0 en la última posición (¿Usar memmove o strdup?) sigo leyendo y cada vez que lea hago strjoin y compruebo si hay un \n, liberando
el aux ya que tengo mis cositas en el string de strdup. AAA XDDDDDD
Hacer esto sucesivamente hasta EOF.
*/