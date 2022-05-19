#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

int	main(void)
{
	int 	deph = 0;
	int 	position = 0;
	int		aim = 0;
	int		file = open("./input.txt", O_RDONLY);
	char	*line = get_next_line(file);

	while (line)
	{
		if (strncmp("forward", line, 7) == 0)
		{
			position += atoi(&line[8]);
			deph += atoi(&line[8]) * aim;
		}
		else if (strncmp("down", line, 4) == 0)
			aim += atoi(&line[5]);
		else if (strncmp("up", line, 2) == 0)
			aim -= atoi(&line[3]);
		free(line);
		line = get_next_line(file);
	}
	close(file);
	printf("Depth: %d \n", deph);
	printf("Position: %d \n", position);
	printf("Result: %d \n", deph * position);
}
