#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

int	part1(char *line);
int	part2(char *line);

int	main()
{
	int 	fd;
	int		count_part1 = 0;
	int		count_part2 = 0;
	char	*line;

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	do
	{
		count_part1 += part1(line);
		count_part2 += part2(line);
		free(line);
		line = get_next_line(fd);
	} while (line);
	printf("Part1 total count: %d\n", count_part1);
	printf("Part2 total count: %d\n", count_part2);
}

void	free2d_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	part1(char *line)
{
	char	**pair = ft_split(line, ',');
	char	**elf1_str = ft_split(pair[0], '-');
	char	**elf2_str = ft_split(pair[1], '-');
	int	elf1[2] = {ft_atoi(elf1_str[0]), ft_atoi(elf1_str[1])};
	int	elf2[2] = {ft_atoi(elf2_str[0]), ft_atoi(elf2_str[1])};
	free2d_array(pair);
	free2d_array(elf1_str);
	free2d_array(elf2_str);
	if (elf1[0] <= elf2[0] && elf1[1]  >= elf2[1])
		return (1);
	if (elf2[0] <= elf1[0] && elf2[1]  >= elf1[1])
		return (1);
	return (0);
}

int	part2(char *line)
{
	char	**pair = ft_split(line, ',');
	char	**elf1_str = ft_split(pair[0], '-');
	char	**elf2_str = ft_split(pair[1], '-');
	int	elf1[2] = {ft_atoi(elf1_str[0]), ft_atoi(elf1_str[1])};
	int	elf2[2] = {ft_atoi(elf2_str[0]), ft_atoi(elf2_str[1])};
	free2d_array(pair);
	free2d_array(elf1_str);
	free2d_array(elf2_str);
	if (elf1[0] >= elf2[0] && elf1[0]  <= elf2[1])
		return (1);
	if (elf1[1] <= elf2[1] && elf1[1]  >= elf2[0])
		return (1);
	if (elf2[0] >= elf1[0] && elf2[0]  <= elf1[1])
		return (1);
	if (elf2[1] <= elf1[1] && elf2[1]  >= elf1[0])
		return (1);
	return (0);
}
