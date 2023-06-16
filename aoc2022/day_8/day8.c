#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

void	count_file_size(int fd);
void	raycast_pos(int pos_x, int pos_y);
void	print_board(int *board, int *high_light, char del);
int		raycast_from_edges();
int		ft_atoi_char(char c);

int board_x = 0;
int board_y = 0;
int	*board = NULL;
int	*board_visible = NULL;

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Please provide input file\n");
		exit(1);
	}

	int 	fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	count_file_size(fd); printf("board x: %d| y: %d\n", board_x, board_y);
	fd = open(argv[1], O_RDONLY);
	board = malloc(sizeof(int) * (board_x * board_y));
	board_visible = calloc(board_x * board_y, sizeof(int));
	ft_bzero(board_visible, sizeof(int) * (board_x * board_y));

	line = get_next_line(fd);
	int x, y = 0;
	while (line)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '\n')
				break ;
			board[(y * board_x) + x] = ft_atoi_char(line[x]);
			x++;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}

	y = 1;
	while (y < board_y - 1)
	{
		x = 1;
		while (x < board_x - 1)
		{
			int pos = y * board_x + x;
			raycast_pos(x, y);
			printf("Raycasting x: %d, y: %d, pos: %d\n", x, y, *(board + pos));
			print_board(board_visible, board_visible + pos, 'a');
			x++;
		}
		y++;
	}
	/* int count_visible = raycast_from_edges(); */
	/* printf("Tress inside grid visible: %d\n", count_visible); */
	/* printf("Tress edges grid: %d\n", (board_x * 2 + board_y * 2 - 4)); */
	/* printf("Total visible: %d\n", count_visible +  (board_x * 2 + board_y * 2 - 4)); */


}

int	check_pos(int *pos, int *highest)
{
	//printf("board[pos]: %d \nboard_visible[pos]: %d\n", board[pos], board_visible[pos]);
	if (*pos > *highest )
	{
		if (!board_visible[pos - board])
		{
			board_visible[pos - board] = 1;
			*highest = *pos;
			return (1);
		}
		*highest = *pos;
	}
	return (0);
}

int	count_tree_sight(int *pos, int tree,int *highest)
{
	if (*pos >= tree)
		return 0;
	if (*pos < *highest )
		return 1;
	if (*pos >  *highest)
		*highest = *pos;
	else
	{
		printf("Erro:  tree: %d, pos: %d, highest: %d\n", tree, *pos, *highest);
		exit(420);
	}
	//board_visible[pos - board] += 1;
	return (1);
}

void	raycast_pos(int pos_x, int pos_y)
{
	int	x = 0;
	int	y = 0;
	int	highest = 0;
	int	*tree = board + pos_y * board_x + pos_x;
	int tmp = 0;

	//  Left to Right
	x = pos_x;
	y = pos_y;
	printf("tree:%d\n", *tree);
	highest = *tree;
	while (++x < board_x)
	{
		tmp += count_tree_sight(board + y * board_x + x, *tree, &highest);
		if (tmp == 0)
			break ;
	}
	if (board_visible[tree - board] == 0)
		board_visible[tree - board] = tmp;
	else if (tmp != 0)
		board_visible[tree - board] *= tmp;


	//  Right to left
	x = pos_x;
	y = pos_y;
	highest = *tree;
	while (--x >= 0)
	{
		tmp += count_tree_sight(board + y * board_x + x, *tree, &highest);
		if (tmp == 0)
			break ;
	}
	if (board_visible[tree - board] == 0)
		board_visible[tree - board] = tmp;
	else if (tmp != 0)
		board_visible[tree - board] *= tmp;

}

int	raycast_from_edges()
{
	int	count = 0;
	int	x = 0;
	int	y = 1;
	int	highest = 0;

	//  Left to Right
	while (y < board_y - 1)
	{
		x = 0;
		highest = board[y * board_x];
		//count++;
		while (++x < board_x - 1)
			count += check_pos(board + y * board_x + x, &highest);
		y++;
	}

	//  Right to Left
	y = 1;
	while (y < board_y - 1)
	{
		x = board_x - 1;
		highest = board[y * board_x + x];
		//count++;
		while (--x > 0)
			if (check_pos(board + y * board_x + x, &highest))
				count++;
		y++;
	}

	// Top to bottom
	x = 1;
	while (x < board_x - 1)
	{
		y = 0;
		highest = board[y * board_x + x];
		while (++y < board_y - 1)
			count += check_pos(board + y * board_x + x, &highest);
		x++;
	}

	// Bottom to Top
	x = 1;
	while (x < board_x - 1)
	{
		y = board_y - 1;
		highest = board[y * board_x + x];
		//count++;
		while (--y > 0)
			count += check_pos(board + y * board_x + x, &highest);
		x++;
	}
	/* printf("Count: %d\n", count); */
	/* printf("Count-4: %d\n", 4 - count); */
	return (count);
}

void	print_board(int *board, int *high_light, char del)
{
	int y = 0;
	while (y < board_y)
	{
		int x = 0;
		while (x < board_x)
		{
			int *pos = &board[y * board_x + x];
			if (high_light && pos == high_light)
				printf("%c%d%c", del, *pos, del);
			else
				printf(" %d ", *pos);
			//printf("board[%d * %d]: %d\n", y, x, board[y * board_x + x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	ft_atoi_char(char c)
{
	char *tmp = malloc(2);
	tmp[0] = c;
	tmp[1] = 0;

	return (ft_atoi(tmp));
}

void	count_file_size(int fd)
{
	char	*line = get_next_line(fd);
	board_x = ft_strlen(line) - 1;
	while (line)
	{
		board_y++;
		free(line);
		line = get_next_line(fd);
	}
}
