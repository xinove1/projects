#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

void	part1();
void	part2();

int	main()
{
	part1();
	part2();
}

void	part1()
{
	int 	fd;
	int		total;
	char	*line;

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	total = 0;
	while (line)
	{
		int flag = 0;
		int	rucksack_sz = (ft_strlen(line) / 2) - 1;

		int i = -1;
		while (++i <= rucksack_sz)
		{
			int j = rucksack_sz;
			while (line[++j] != '\n')
			{
				if (line[i] == line[j])
				{
					if (line[i] >= 'a' && line[i] <= 'z')
						total += line[i] - 'a' + 1;
					if (line[i] >= 'A' && line[i] <= 'Z')
						total += line[i] - 'A' + 26 + 1;
					flag = 1;
					break;
				}
			}
			if (flag)
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	printf("Part 1 total: %d\n", total);
}

void	part2()
{
	int 	fd;
	int		total;
	char	*line[3];

	fd = open("input", O_RDONLY);
	line[0] = get_next_line(fd);
	line[1] = get_next_line(fd);
	line[2] = get_next_line(fd);
	total = 0;
	while (line[2])
	{
		int flag = 0;
		int i = -1;
		while (line[0][++i])
		{
			int j = -1;
			while (line[1][++j])
			{
				if (line[0][i] == line[1][j])
				{
					int	k = -1;
					while (line[2][++k])
					{
						if (line[0][i] == line[2][k])
							flag = line[0][i];
					}
					break ;
				}
			}
			if (flag)
				break ;
		}
		if (flag == 0)
			printf("ERROR\n");
		if (flag >= 'a' && flag <= 'z')
			total += flag - 'a' + 1;
		if (flag >= 'A' && flag <= 'Z')
			total += flag - 'A' + 26 + 1;
		free(line[0]);
		free(line[1]);
		free(line[2]);
		line[0] = get_next_line(fd);
		line[1] = get_next_line(fd);
		line[2] = get_next_line(fd);
	}
	printf("Total: %d\n", total);
}
