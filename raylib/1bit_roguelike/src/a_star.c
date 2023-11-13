#include "game.h"

typedef struct Node
{
	Vector2		pos;
	struct Node	*prev;
	int			priority; // NOTE cost + herustic to end
	int			cost; // NOTE cost to reach node from beggining
} Node;

static void	debug_draw_nodes(List *frontier, Color color);

static List *get_priority(List **list);
static Node	*create_node(Arena *arena, Vector2 pos, Node *prev, int global_cost, int cost);
static int	lstremove(List **list, List *remove);
static int	heuristic(Vector2 a, Vector2 b);
static List	*lstfind_node(List *list, Vector2 pos);
Node	*a_star(Vector2 start, Vector2 target, Arr2D map, Arena *arena_nodes);
static int	next_neighbor(Node **neighbor, Node *node, List **nodes, Arena *arena_lst, Arena *arena_nodes, Arr2D map);

void	pathfind_a_star(Path *path, Vector2 start, Vector2 target, Arr2D map)
{
	Arena	*arena_nodes = arena_create_sized(sizeof(Node), 200);
	Node	*target_node = a_star(start, target, map, arena_nodes);

	List	*path_lst = NULL;
	Node	*current = target_node;
	while (current)
	{
		void	*mem = pool_alloc(path->mem); // NOTE Assumes path.mem is a pool alloc of (sizeof(List) + sizeof(Vector2))
		List	*new = mem;
		Vector2	*pos = mem + sizeof(List);
		*pos = current->pos;
		new->content = pos;
		new->next = NULL;
		lstadd_back(&path_lst, new);
		current = current->prev;
	}
	path->head = path_lst;
	path->current = path_lst;
	arena_destroy(arena_nodes);
}

// NOTE check if start/target is inside map
Node	*a_star(Vector2 start, Vector2 target, Arr2D map, Arena *arena_nodes)
{
	Arena	*arena_lst = arena_create_sized(sizeof(List), 10);
	Node	*start_node = create_node(arena_nodes, start, NULL, 0, 0);
	List	*nodes  = lstnew(arena_lst, start_node);
	List	*frontier = lstnew(arena_lst, start_node);

	while (frontier)
	{
		List	*current = get_priority(&frontier);
		Node	*current_node = current->content;

		if (Vector2Compare(current_node->pos, target))
		{
			arena_destroy(arena_lst);
			return (current_node);
		}

		Node	*neighbor = NULL;
		while (next_neighbor(&neighbor, current_node, &nodes, arena_lst, arena_nodes, map))
		{
			if (get_array(map.arr, neighbor->pos) == COLLISION)
			{
				if (Vector2Compare(neighbor->pos, target))
					goto out;
				continue ;
			}
			int	new_cost = current_node->cost + get_array(map.arr, neighbor->pos) + 1; // NOTE map current has 0 for normal tiles but value of traversal needs to be at least one, so +1
			if (neighbor->cost == 0 || new_cost < neighbor->cost)
			{
				neighbor->cost = new_cost;
				neighbor->priority = new_cost + heuristic(neighbor->pos, target);
				neighbor->prev = current_node;
				lstadd_back(&frontier, lstnew(arena_lst, neighbor));
			}
		}
		pool_free(arena_lst, current);
	}
	out:
	printf("a_star target not found\n");
	arena_destroy(arena_lst);
	return (NULL);
}

static void	debug_draw_nodes(List *frontier, Color color)
{
	List	*i = frontier;
	while (i)
	{
		Node	*node = i->content;
		Position	pos = (Position) {node->pos.x * TILE_SZ, node->pos.y * TILE_SZ};
		DrawRectangle(pos.x, pos.y, TILE_SZ, TILE_SZ, ColorAlpha(color, 0.3));
		i = i->next;
	}
}

// Manhattan distance on a square grid
static int	heuristic(Vector2 a, Vector2 b)
{
	return (abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y));
}

static int	next_neighbor(Node **neighbor, Node *node, List **nodes, Arena *arena_lst, Arena *arena_nodes, Arr2D map)
{
	static int	i = 0;
	Vector2	add[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	if (i == 4)
	{
		i = 0;
		return (0);
	}

	Vector2	new_pos = Vector2Add(node->pos, add[i]);
	if (new_pos.x < 0 || new_pos.x >= map.size.x || new_pos.y < 0 || new_pos.y >= map.size.y)
	{
		i++;
		return (next_neighbor(neighbor, node, nodes, arena_lst, arena_nodes, map));
	}

	List	*neighbor_lst = lstfind_node(*nodes, new_pos);
	if (neighbor_lst)
		*neighbor = neighbor_lst->content;
	else
		*neighbor = NULL;

	if (*neighbor && *neighbor == node->prev)
	{
		i++;
		return (next_neighbor(neighbor, node, nodes, arena_lst, arena_nodes, map));
	}
	if (*neighbor == NULL)
	{
		/* printf("creating node \n"); */
		/* printf("from:    %f,%f\n", node->pos.x, node->pos.y); */
		/* printf("new_pos: %f,%f\n\n", new_pos.x, new_pos.y); */
		Node	*new_node = create_node(arena_nodes, new_pos, node, 0, 0);
		*neighbor = new_node;
		lstadd_back(nodes, lstnew(arena_lst, new_node));
	}
	i++;
	return (1);
}


static List	*lstfind_node(List *list, Vector2 pos)
{
	while (list)
	{
		Node	*node = list->content;
		if (node->pos.x == pos.x && node->pos.y == pos.y)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static List *get_priority(List **list)
{
	List	*i = *list;
	List	*smaller = *list;
	while (i)
	{
		Node	*smaller_ =  smaller->content;
		Node	*current = i->content;
		//printf("i->next %p\n", i->next);
		if (current->priority < smaller_->priority)
			smaller = i;
		i = i->next;
	}
	lstremove(list, smaller);
	return (smaller);
}

static Node	*create_node(Arena *arena, Vector2 pos, Node *prev, int global_cost, int cost)
{
	Node	*node = pool_alloc(arena);

	node->pos = pos;
	node->prev = prev;
	node->priority = global_cost;
	node->cost = cost;
	return (node);
}

static int	lstremove(List **list, List *remove)
{
	List	*i = *list;

	if (i == remove)
	{
		*list = i->next;
		i->next = NULL;
		return (0);
	}
	while (i)
	{
		if (i->next == remove)
		{
			List	*tmp = i->next;
			i->next = tmp->next;
			tmp->next = NULL;
			return (0);
		}
		i = i->next;
	}
	return (1);
}
