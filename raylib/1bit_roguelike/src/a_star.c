#include "game.h"

typedef struct Node
{
	Vector2		pos;
	struct Node	*prev;
	int			global_cost; // NOTE priority when choosing from frontier, rename?
	int			cost;
} Node;

static List *get_priority(List *list);
static Node	*create_node(Arena *arena, Vector2 pos, Node *prev, int global_cost, int cost);
static int	lstremove(List **list, List *remove);
static int	get_next_neighbor(List **neighbor, Node *node, List *frontier, List *visited, Arena *arena_lst, Arena *arena_node, Arr2D map);
static int	heuristic(Vector2 a, Vector2 b);

List	*a_star(Vector2 start, Vector2 target, Arena *lists_arena, Arena *nodes_arena, Arr2D map);
void	pathfind_a_star(Path *path, Vector2 start, Vector2 target, Arr2D map)
{
	Arena	*list_arena = arena_create_sized(sizeof(List), 200);
	Arena	*nodes_arena = arena_create_sized(sizeof(Node), 200);
	List	*target_node = a_star(start, target, list_arena, nodes_arena, map);

	List	*path_ = NULL;
	Node	*current = target_node->content; // remove target_node, typecast directaly to Node
	while (current)
	{
		void	*mem = pool_alloc(path->memL); // NOTE Assumes path.memL is a pool alloc of (sizeof(List) + sizeof(Vector2))
		List	*new = mem;
		Vector2	*pos = mem + sizeof(List);
		*pos = current->pos;
		new->content = pos;
		new->next = NULL;
		lstadd_back(&path_, new);
		current = current->prev;
	}
	path->head = path_;
	path->current = path_;
	arena_destroy(list_arena);
	arena_destroy(nodes_arena);
}

List	*a_star(Vector2 start, Vector2 target, Arena *lists_arena, Arena *nodes_arena, Arr2D map)
{
	List	*frontier = NULL;
	List	*visited = NULL;

	Node	*start_node = create_node(nodes_arena, start, NULL, heuristic(start, target), 0);
	lstadd_back(&frontier, lstnew(lists_arena, start_node));

	while (frontier)
	{
		printf("while frontier\n");
		List	*current = get_priority(frontier);
		printf("tadoba\n");
		Node	*current_node = current->content;

		if (Vector2Compare(current_node->pos, target))
			return (current);

		List	*neighbor_lst;
		// NOTE get neighbor should add neighbors to visited list
		/* printf("-------------------------------------\n"); */
		while (get_next_neighbor(&neighbor_lst, current_node, frontier, visited, lists_arena, nodes_arena, map))
		{
			/* printf("while get_next_neighbor\n"); */
			Node	*neighbor = neighbor_lst->content;
			if (get_array(map.arr, neighbor->pos) == COLLISION && !Vector2Compare(neighbor->pos, target))
			{
				pool_free(lists_arena, neighbor_lst);
				pool_free(nodes_arena, neighbor);
				continue ;
			}
			// TODO check map bounds or do a get_map that checks bounds
			int	new_cost = current_node->cost + get_array(map.arr, neighbor->pos);
			if (neighbor->cost == 0 || new_cost < neighbor->cost)
			{
				neighbor->cost = new_cost;
				neighbor->global_cost = neighbor->cost + heuristic(neighbor->pos, target); // NOTE needed?
				neighbor->prev = current_node;
				lstadd_back(&frontier, neighbor_lst);
			}
			/* printf("end of while get_next_neghbor\n"); */
		}
		lstremove(&frontier, current);
		lstadd_back(&visited, current);
		/* printf("end of while frontier\n"); */
	}
	printf("[INFO] a_star didn't find path to target\n");
	return (NULL);
}

// Manhattan distance on a square grid
static int	heuristic(Vector2 a, Vector2 b)
{
	return (abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y));
}

static List	*lstfind_node(List *list, Vector2 pos);
static int	get_next_neighbor(List **neighbor, Node *node, List *frontier, List *visited, Arena *arena_lst, Arena *arena_node, Arr2D map)
{
	static int	i = 0;
	Vector2	add[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

//	printf("i: %d\n",i);
	if (i == 4)
	{
		i = 0;
		return (0);
	}
	Vector2	new_pos = Vector2Add(node->pos, add[i]);
	if (new_pos.x < 0 || new_pos.x >= map.size.x || new_pos.y < 0 || new_pos.y >= map.size.y)
	{
		i++;
		return (get_next_neighbor(neighbor, node, frontier, visited, arena_lst, arena_node, map));
	}
	// NOTE check on frontier too?
	*neighbor = lstfind_node(visited, new_pos);
	if (*neighbor && (*neighbor)->content == node->prev)
	{
		assert(1);
		i++;
		return (get_next_neighbor(neighbor, node, frontier, visited, arena_lst, arena_node, map));
	}
	if (*neighbor != NULL)
		lstremove(&visited, *neighbor);
	else
	{
		printf("creating node \n");
		printf("from:    %f,%f\n", node->pos.x, node->pos.y);
		printf("new_pos: %f,%f\n\n", new_pos.x, new_pos.y);
		Node	*new_node = create_node(arena_node, new_pos, node, 0, 0);
		*neighbor = lstnew(arena_lst, new_node);
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

static List *get_priority(List *list)
{
	List	*i = list;
	List	*smaller = list;
	while (i)
	{
		Node	*smaller_ =  smaller->content;
		Node	*current = i->content;
		//printf("i->next %p\n", i->next);
		if (current->global_cost < smaller_->global_cost)
			smaller = i;
		i = i->next;
	}
	return (smaller);
}

static Node	*create_node(Arena *arena, Vector2 pos, Node *prev, int global_cost, int cost)
{
	Node	*node = pool_alloc(arena);

	node->pos = pos;
	node->prev = prev;
	node->global_cost = global_cost;
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
