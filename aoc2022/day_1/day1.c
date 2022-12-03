#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

int	main()
{
	int 	fd;
	int		flag;
	int		current_calories;
	int		top1_calories;
	int		top2_calories;
	int		top3_calories;
	char	*line;

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	top1_calories = 0;
	top2_calories = 0;
	top3_calories = 0;
	current_calories = 0;
	do
	{
		int calories = ft_atoi(line);
		if (calories == 0)
		{
			if (current_calories > top1_calories)
			{
				top3_calories = top2_calories;
				top2_calories = top1_calories;
				top1_calories = current_calories;
			}
			else if (current_calories > top2_calories)
			{
				top3_calories = top2_calories;
				top2_calories = current_calories;
			}
			else if (current_calories > top3_calories)
				top3_calories = current_calories;
			current_calories = 0;
		}
		else
			current_calories += calories;
		free(line);
		line = get_next_line(fd);
	} while (line);
	printf("Max calories (top1): %d\n", top1_calories);
	printf("Top 2 calories: %d\n", top2_calories);
	printf("Top 3 calories: %d\n", top3_calories);
	printf("Top 3 summed: %d\n", top1_calories + top2_calories + top3_calories);
}
