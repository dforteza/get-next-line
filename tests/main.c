#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
** Uso:
**   ./gnl <archivo>   -> lee de ese archivo
**   ./gnl             -> lee de stdin   (ej:  echo "hola" | ./gnl )
**
** Imprime cada línea entre marcadores [ ] para ver EXACTAMENTE
** dónde empieza/termina y si lleva el '\n' incluido.
*/
int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error abriendo: %s\n", argv[1]);
			return (1);
		}
	}
	else
		fd = 0;
	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("línea %d -> [%s]\n", i++, line);
		free(line);
	}
	printf("--- fin (gnl devolvió NULL) ---\n");
	if (fd > 0)
		close(fd);
	return (0);
}
