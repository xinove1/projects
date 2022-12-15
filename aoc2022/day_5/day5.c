#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	part1();
void	part2();

int		count_crates_depth(char *file);
char	**get_crates_lines(char *file, int crate_depths);
t_stack	**get_cargo(char	*file);

int	main()
{
	/* t_stack	*stack = StackNew('a'); */
	/* StackAddBack(&stack, StackNew('b')); */
	/* StackAddBack(&stack, StackNew('c')); */
	/* StackAddBack(&stack, StackNew('d')); */
	/* StackAddBack(&stack, StackNew('e')); */


	/* t_stack	*stack2 = StackNew('f'); */
	/* StackAddBack(&stack2, StackNew('g')); */
	/* StackAddBack(&stack2, StackNew('h')); */
	/* StackAddBack(&stack2, StackNew('i')); */
	/* StackAddBack(&stack2, StackNew('j')); */

	/* StackPrint(stack); */
	/* StackPrint(stack2); */
	/* StackMoveMany(&stack, &stack2, 5); */
	/* StackPrint(stack); */
	/* StackPrint(stack2); */
	part1();
	part2();
}

void	free2d_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	part2()
{
	int 	fd;
	int		flag;
	char	*line;
	t_stack	**cargo;

	flag = 0;
	cargo = get_cargo("input");
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	//StackPrintMany(cargo);
	while (line)
	{
		if (flag && strcmp(line, "\n"))
		{
			char	**str = ft_split(line, ' ');
			StackMoveManyOrder(&(cargo[atoi(str[3])]) - 1, &(cargo[atoi(str[5])]) - 1, atoi(str[1]));
			free2d_array(str);
		}
		if (!flag && !strcmp(line, "\n"))
			flag = 1;
		free(line);
		line = get_next_line(fd);
	}
	// Clean stacks
	for (int i = 0; cargo[i]; i++)
		printf("%c", (StackGetLast(cargo[i]))->crate);
	printf("\n");
	close(fd);
}

void	part1()
{
	int 	fd;
	int		flag;
	char	*line;
	t_stack	**cargo;

	flag = 0;
	cargo = get_cargo("input");
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
//	StackPrintMany(cargo);
	while (line)
	{
		if (flag && strcmp(line, "\n"))
		{
			char	**str = ft_split(line, ' ');
			/* for (int i = 0; str[i]; i++) */
			/* 	printf("str[%d]: %s\n", i, str[i]); */
			StackMoveMany(&(cargo[atoi(str[3])]) - 1, &(cargo[atoi(str[5])]) - 1, atoi(str[1]));
			free2d_array(str);
		}
		if (!flag && !strcmp(line, "\n"))
			flag = 1;
		free(line);
		line = get_next_line(fd);
	}
	// Clean stacks
	for (int i = 0; cargo[i]; i++)
		printf("%c", (StackGetLast(cargo[i]))->crate);
	printf("\n");
	close(fd);
}

t_stack	**get_cargo(char	*file)
{
	char	**lines;
	t_stack	**cargo;
	int		crates_depth;
	int		i;


	crates_depth = count_crates_depth(file); //printf("crates_depth: %d\n", crates_depth);
	lines = get_crates_lines(file, crates_depth);
	cargo = malloc(sizeof(t_stack *) *  crates_depth + 1); // NOTE +1 for NULL?
	/* for (int i = 0; i < crates_depth - 1; i++) */
	/* 	StackAddBack(&cargo[i], StackNew('0' + i)); */
	cargo[crates_depth] = NULL;

	i = crates_depth - 1;
	while (--i >= 0)
	{
		int offset = 1;
		int	j = 0;
		while (lines[i][offset])
		{
			//printf("%c ", lines[i][offset]);
			if (ft_isalpha(lines[i][offset]))
				StackAddBack(&cargo[j], StackNew(lines[i][offset]));
			offset += 4;
			j++;
		}
		//printf("\nlines[%d]: %s\n", i, lines[i]);
	}
	free2d_array(lines);
	return (cargo);
}

char	**get_crates_lines(char *file, int crates_depth)
{
	int 	fd;
	char	*line;
	char	**lines;
	int	i;

	i = 0;
	lines = malloc(sizeof(char *) * crates_depth + 1);
	lines[crates_depth] = NULL;
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!strcmp(line, "\n"))
		{
			free(line);
			break ;
		}
		lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	count_crates_depth(char *file)
{
	int	i;
	int 	fd;
	char	*line;

	i = 0;
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!strcmp(line, "\n"))
			break ;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}
