#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

void	cycle(char *line);

int	cycle_count = 0;
int	cycle_signal = 20;
int	cycle_strength_sum = 0;
int	x = 1;
int	pixel_pos = 0;

void	print_pixel();

int	main(int argc, char **argv)
{
	int 	fd;
	char	*line;

	if (argc != 2)
	{
		printf("please provide input file\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		cycle(line);
		free(line);
		line = get_next_line(fd);
		//printf("\n");
	}
	printf("Cycle Strength sum %d\n", cycle_strength_sum);
}


void	cycle(char *line)
{

	cycle_count++;
	print_pixel();
	if (!ft_strncmp(line, "addx", 4))
	{
		cycle_count++;
		print_pixel();
		if (cycle_count >= cycle_signal)
		{
			cycle_strength_sum += x * cycle_signal;
			cycle_signal += 40;
		}
		x += ft_atoi(line + 4);
	}
}

void	print_pixel()
{
	if (pixel_pos == x || pixel_pos == x - 1 || pixel_pos == x + 1)
		printf("#");
	else
		printf(".");
	if (pixel_pos == 39)
	{
		pixel_pos = 0;
		printf("\n");
	}
	else
		pixel_pos += 1;
}
