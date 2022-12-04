#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

int	main()
{
	int 	fd;
	char	*line;

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	do
	{
		free(line);
		line = get_next_line(fd);
	} while (line);
}
