#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"


void	part_1();
void	part_2();

int	main()
{
	part_1();
	part_2();
}

// ROCK     A X
// PAPER    B Y
// SCISSORS C Z
void	part_1()
{
	int 	fd;
	int		total_score;
	char	*line;

	total_score = 0;
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		char	**round = ft_split(line, ' ');
		int	elf = round[0][0];
		int	me = round[1][0];
		free(round);

		if (me == 'X')
			total_score += 1;
		if (me == 'Y')
			total_score += 2;
		if (me == 'Z')
			total_score += 3;

		if (me == 'X' && elf == 'A')
			total_score += 3;
		if (me == 'Y' && elf == 'B')
			total_score += 3;
		if (me == 'Z' && elf == 'C')
			total_score += 3;

		if (me == 'X' && elf == 'C')
			total_score += 6;
		if (me == 'Y' && elf == 'A')
			total_score += 6;
		if (me == 'Z' && elf == 'B')
			total_score += 6;
		free(line);
		line = get_next_line(fd);
	}
	printf("Part 1 Total score: %d\n", total_score);
}

// ROCK     A
// PAPER    B
// SCISSORS C
// X lose
// Y draw
// Z win
int	choose_play(int elf_play, int condition);
void	part_2()
{
	int 	fd;
	int		total_score;
	char	*line;

	total_score = 0;
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		char	**round = ft_split(line, ' ');
		int	elf = round[0][0];
		int	me = choose_play(elf, round[1][0]);
		free(round);

		if (me == 'X')
			total_score += 1;
		if (me == 'Y')
			total_score += 2;
		if (me == 'Z')
			total_score += 3;

		if (me == 'X' && elf == 'A')
			total_score += 3;
		if (me == 'Y' && elf == 'B')
			total_score += 3;
		if (me == 'Z' && elf == 'C')
			total_score += 3;

		if (me == 'X' && elf == 'C')
			total_score += 6;
		if (me == 'Y' && elf == 'A')
			total_score += 6;
		if (me == 'Z' && elf == 'B')
			total_score += 6;
		free(line);
		line = get_next_line(fd);
	}
	printf("Part 2 Total score: %d\n", total_score);
}

int	choose_play(int elf, int condition)
{
	if (elf == 'A')
	{
		if (condition == 'X')
			return ('Z');
		if (condition == 'Y')
			return ('X');
		if (condition == 'Z')
			return ('Y');
	}
	if (elf == 'B')
	{
		if (condition == 'X')
			return ('X');
		if (condition == 'Y')
			return ('Y');
		if (condition == 'Z')
			return ('Z');
	}
	if (elf == 'C')
	{
		if (condition == 'X')
			return ('Y');
		if (condition == 'Y')
			return ('Z');
		if (condition == 'Z')
			return ('X');
	}
	printf("ERROR\n");
	return (0);
}
