#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
** Uso: ./gnl_bonus
** Abre 3 ficheros y lee una línea de cada uno por turno.
** Si el bonus funciona, las líneas de cada fd salen en orden y sin mezclarse.
*/

/* Lee una línea de fd, la imprime y la libera. Devuelve 1 si leyó algo, 0 si NULL. */
static int	read_one(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	printf("fd %d -> [%s]\n", fd, line);
	free(line);
	return (1);
}

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	int	flag;

	fd1 = open("tests/normal.txt", O_RDONLY);
	fd2 = open("tests/una_linea.txt", O_RDONLY);
	fd3 = open("tests/sin_salto.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("Error abriendo ficheros\n");
		return (1);
	}
	flag = 1;
	while (flag)
	{
		flag = 0;
		if (read_one(fd1))
			flag = 1;
		if (read_one(fd2))
			flag = 1;
		if (read_one(fd3))
			flag = 1;
	}
	printf("--- fin ---\n");
	printf("fd -1   -> %p\n", (void *)get_next_line(-1));
	printf("fd 1024 -> %p\n", (void *)get_next_line(MAX_FD));
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
