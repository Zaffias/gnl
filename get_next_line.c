#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
static size_t	line_read(char *raw_line)
{
	size_t	i;

	i = 0;
	while(raw_line[i] != '\n' && raw_line[i])
		i++;
	return(i);
}
char	*get_next_line(int fd)
{
	ssize_t		bytes_rd;
	char		buffer[BUFFER_SIZE + 1];
	static char	*rem[65535];
	char		*aux;
	char		*res;

	bytes_rd = 1;
	while(bytes_rd > 0)
	{
		bytes_rd = read(fd , buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = 0;
		if(!rem[fd])
			rem[fd] = ft_strdup("");
		aux = ft_strjoin(rem[fd], buffer);
		free(rem[fd]);
		rem[fd] = aux;
		if (ft_strchr(rem[fd],'\n'))
			break;
	}
	res = ft_substr(rem[fd], 0, line_read(rem[fd]) + 1);
	rem[fd] = ft_substr(rem[fd], line_read(rem[fd]) + 1, BUFFER_SIZE - line_read(rem[fd]));
	printf("Resultado: %s",res);
	//printf("Restante: %s",rem[fd]);
	return(res);
}
int main()
{
	int fd = open("b",O_RDONLY);
	int i = 0;
	while(i < 11)
	{
		get_next_line(fd);
		i++;
	}

}

/* Read recuerda la posición del archivo en la que estaba en cada llamada, por lo que
puedo leer, después comprobar si en el buffer está \n, si es así devolver hasta ahí y guardar
el restante de lo leído (si lo hay) a rem (¿Qué pasa si leo todo de golpe?); si no es así  guardo buff en un auxiliar en el heap,
añadiendole un \0 en la última posición (¿Usar memmove o strdup?) sigo leyendo y cada vez que lea hago strjoin y compruebo si hay un \n, liberando
el aux ya que tengo mis cositas en el string de strdup. AAA XDDDDDD
Hacer esto sucesivamente hasta EOF.
*/