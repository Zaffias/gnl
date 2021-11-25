#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t			bytes_rd;
	char			buff[BUFFER_SIZE + 1];
	static	char	*rem;
	char			*aux;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	bytes_rd = 1;
	while (bytes_rd > 0)//No sé como poner la condición, pero sería cuando read devuelva 0 o -1 ya que está en EOF o ha dado error
	{
		bytes_rd = read(fd, buff, BUFFER_SIZE);
		buff[bytes_rd] = '\0';
		if(!rem) // ¿Necesito un doble puntero?
			rem = ft_strdup("");
		aux = ft_strjoin(rem, buff);
		free(rem);
		rem = aux;
		free(aux);
		if (ft_strchr(rem,'\n'))
			break ;
	}
	
}

int main()
{
	int fd = open("b", 00, 0x00644);
	ssize_t bytes_rd;
	char buffer [50];

	if (fd == -1)
		return 1;
	bytes_rd = read(fd, buffer, 5);
	printf("bytes leidos: %d\nstring:%s\n",bytes_rd, buffer);
	bytes_rd = read(fd, buffer, 5);
	printf("bytes leidos: %d\nstring:%s\n",bytes_rd, buffer);
}
/* Read recuerda la posición del archivo en la que estaba en cada llamada, por lo que
puedo leer, después comprobar si en el buffer está \n, si es así devolver hasta ahí y guardar
el restante de lo leído (si lo hay) a rem (¿Qué pasa si leo todo de golpe?); si no es así  guardo buff en un auxiliar en el heap,
añadiendole un \0 en la última posición (¿Usar memmove o strdup?) sigo leyendo y cada vez que lea hago strjoin y compruebo si hay un \n, liberando
el aux ya que tengo mis cositas en el string de strdup. AAA XDDDDDD
Hacer esto sucesivamente hasta EOF.
*/