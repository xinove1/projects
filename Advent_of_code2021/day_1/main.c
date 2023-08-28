#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#define INPUT_SIZE 2000

int	part_1(int	numbers[INPUT_SIZE]);
int	part_2(int	numbers[INPUT_SIZE]);

int	main()
{
	int		numbers[2000];
	int		file = open("./input.txt", O_RDONLY);
	char	*line = get_next_line(file);
	int		i = 0;

	while(line)
	{
		numbers[i] = atoi(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
	printf("Count part 1: %d \n", part_1(numbers));
	printf("Count part 2: %d \n", part_2(numbers));
	close(file);
}

int	part_1(int	numbers[INPUT_SIZE])
{
	int	count = 0;
	int	i = 1;

	while(i < INPUT_SIZE)
	{
		if (numbers[i] > numbers[i - 1])
			count++;
		i++;
	}
	return (count);
}

int	part_2(int	numbers[INPUT_SIZE])
{
	int count = -1;
	int	i = 0;
	int previous = 0;
	int	sum;
	while (i < INPUT_SIZE - 2 )
	{
		sum = numbers[i] + numbers[i + 1] + numbers[i + 2];
		if (sum > previous)
			count++;
		previous = sum;
		i++;
	}
	return (count);
}
