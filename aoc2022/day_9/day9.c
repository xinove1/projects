#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"
#define ROPE_SIZE 10
#define RIGHT 'R'
#define LEFT 'L'
#define DOWN 'D'
#define UP 'U'
#define UP_LEFT 'Q'
#define UP_RIGHT 'E'
#define DOWN_LEFT 'Z'
#define DOWN_RIGHT 'C'

typedef struct s_vector2
{
	int	x;
	int	y;
} vector2;

typedef struct s_visited
{
	vector2	pos;
	int		count;
} visited;

typedef struct s_node
{
	vector2			pos;
	struct s_node	*tail;
} node;

void	print_visited(visited v);
void	move_pos(node *pos, char dir);
int 	move_tail_node(node *tail, node *head, char dir);
void	move(char dir, int times);
int		head_in_range(node *tail, node *head);
void	print_board(int size);
void	update_visited(node tail);

node	HEAD = {0};
node	*TAIL = NULL;
t_list	*list = NULL;

int	main(int argc, char **argv)
{
	int 	fd;
	char	*line;

	if (argc != 2)
	{
		printf("Please provide input file\n");
		exit(1);
	}

	visited	start = {(vector2) {0, 0}, 0};
	ft_lstadd_back(&list, ft_lstnew(&start));
	// TODO init all nodes
	node *tmp_previous = &HEAD;
	for (int i = 0; i < ROPE_SIZE - 1; i++)
	{
		node *tmp = calloc(1, sizeof(node));
		tmp->pos = (vector2){0, 0};
		tmp->tail = NULL;
		tmp_previous->tail = tmp;
		tmp_previous = tmp;
	}
	TAIL = tmp_previous;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	print_board(17);
	while (line)
	{
		move(line[0], ft_atoi(&line[2]));
		printf("== %c %d == \n", line[0], ft_atoi(&line[2]));
		free(line);
		line = get_next_line(fd);
	}

	// part one
	t_list	*i = list;
	int		count = 0;

	while (i)
	{
		count++;
		i = i->next;
	}
	printf("Count: %d\n", count);
}

void	move(char dir, int times)
{
	int	i = 0;
	while (i < times)
	{
		move_pos(&HEAD, dir);
		move_tail_node(HEAD.tail, &HEAD, dir);
		update_visited(*TAIL);
		i++;
	}
}

void	update_visited(node tail)
{
	t_list	*i = list;
	int		found = 0;

	while (i)
	{
		visited	*tmp = i->content;
		if (tmp->pos.x == tail.pos.x && tmp->pos.y == tail.pos.y)
		{
			found = 1;
			tmp->count++;
			break ;
		}
		i = i->next;
	}
	if (found == 0)
	{
		visited	*new = calloc(1, sizeof(visited));
		new->count = 1;
		new->pos = tail.pos;
		ft_lstadd_back(&list, ft_lstnew(new));
	}
}

int move_tail_node(node *tail, node *head, char dir)
{
	vector2	tailp = tail->pos;
	vector2	headp = head->pos;
	int	dif_x = headp.x - tailp.x;
	int	dif_y = headp.y - tailp.y;
	//printf("tail.pos: (%d, %d), head.pos: (%d, %d)\n", tailp.x, tailp.y, headp.x, headp.y);
	if (head_in_range(tail, head))
		return 0;
	if (headp.x == tailp.x || headp.y == tailp.y)
	{
		if (dif_x > 0)
			dir = RIGHT;
		else if (dif_x < 0)
			dir = LEFT;
		else if (dif_y > 0)
			dir = UP;
		else if (dif_y < 0)
			dir = DOWN;
		move_pos(tail, dir);
	}
	else
	{
		if (!(dif_x > 0 || dif_x  < 0 || dif_y > 0 || dif_y < 0))
		{
			printf("erro move tail, dir: %c\n", dir) ;
			print_board(15);
			exit(1);
		}
		if      ((dir == UP && dif_x == 1) || (dir == RIGHT && dif_y > 0))
			dir = UP_RIGHT;
		else if ((dir == UP && dif_x == -1) || (dir == LEFT && dif_y > 0))
			dir = UP_LEFT;
		else if ((dir == DOWN && dif_x == 1) || (dir == RIGHT && dif_y < 0))
			dir = DOWN_RIGHT;
		else if ((dir == DOWN && dif_x == -1) || (dir == LEFT && dif_y < 0))
			dir = DOWN_LEFT;
		move_pos(tail, dir);
	}
	if (tail->tail)
		move_tail_node(tail->tail, tail, dir);
	return (1);
}

void	move_pos(node *pos, char dir)
{
	//printf("node.pos: %d, %d, dir: %c\n", pos->pos.x , pos->pos.x, dir);
	switch (dir) {
		case RIGHT:
			pos->pos.x++;
			break;
		case LEFT:
			pos->pos.x--;
			break;
		case UP:
			pos->pos.y++;
			break;
		case DOWN:
			pos->pos.y--;
			break;
		case UP_LEFT:
			pos->pos.y++;
			pos->pos.x--;
			break;
		case UP_RIGHT:
			pos->pos.y++;
			pos->pos.x++;
			break;
		case DOWN_LEFT:
			pos->pos.y--;
			pos->pos.x--;
			break;
		case DOWN_RIGHT:
			pos->pos.y--;
			pos->pos.x++;
			break;
		default:
			printf("ERROR THIS HOULDOSEUND\n");
			exit(1);
			break ;
	}
}

int	head_in_range(node *tail, node *head)
{
	int	dif_x = head->pos.x - tail->pos.x;
	int	dif_y = head->pos.y - tail->pos.y;
	if ((dif_x == 1 || dif_x == -1 || dif_x == 0) && (dif_y == 1 || dif_y == -1 || dif_y == 0))
		return (1);
	return (0);
}

void	print_board(int size)
{
	int	x = 0;
	int	y = size;
	while (--y >= -size)
	{
		x = -size;
		while (++x < size)
		{
			int	flag = 1;
			node	*tmp = &HEAD;
			int		i = 0;
			while (tmp)
			{
				if (tmp->pos.x == x && tmp->pos.y == y)
				{
					if (i == 0)
						printf("H");
					else
						printf("%d", i);
					flag = 0;
					break ;
				}
				i++;
				tmp = tmp->tail;
			}
			if (flag && x == 0 && y == 0)
				printf("S");
			else if(flag)
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

void	print_visited(visited v)
{
	printf("Visited (%d, %d), %d times\n", v.pos.x, v.pos.y, v.count);
}
