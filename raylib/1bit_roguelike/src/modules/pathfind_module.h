#ifndef PATHFIND_MODULE_H_
# define PATHFIND_MODULE_H_
# include "../includes.h"
# include "basic_components_module.h"

typedef struct
{
	Arena	*mem;
	List	*head;
	List	*current;
} Path;

extern ECS_COMPONENT_DECLARE(Path);

void	pathfind_a_star(Path *path, Vector2 start, Vector2 target, Arr2D map);
void	PathfindImport(ecs_world_t *ecs);
void	_render_paths(ecs_iter_t *it);
Vector2	*next_path_pos(Path *path);
Vector2	next_path_dir(Path *path);

#endif

#ifdef PATHFIND_MODULE_IMPLEMENTATION

ECS_COMPONENT_DECLARE(Path);

static Arena	*_nodes_arena = NULL;

static void _pathfind_atfini(ecs_world_t *ecs, void *ctx)
{
	if (_nodes_arena)
		arena_destroy(_nodes_arena);
}

void	PathfindImport(ecs_world_t *ecs)
{
	ECS_MODULE(ecs, Pathfind);
	ECS_COMPONENT_DEFINE(ecs, Path);
	ECS_SYSTEM(ecs, _render_paths, OnDraw2D, Path); // TODO make optional & debug only
	ecs_atfini(ecs, _pathfind_atfini, NULL);
}

// Returns Dir
Vector2	next_path_dir(Path *path)
{
	if (path->current == NULL || path->current->next == NULL)
		return ((Vector2){0, 0});
	Vector2	current = *(Vector2 *)path->current->content;
	path->current = path->current->next;
	Vector2	next = *(Vector2 *)path->current->content;
	return (Vector2Subtract(next, current));
}

Vector2	*next_path_pos(Path *path)
{
	if (path->current == NULL)
		return (NULL);
	Vector2	*pos = path->current->content;
	path->current = path->current->next;
	return (pos);
}

void	_render_paths(ecs_iter_t *it)
{
	Path	*path = ecs_field(it, Path, 1);

	// TODO change color for each path
	for (int i = 0; i < it->count; i++)
	{
		if (!path[i].current)
			continue;
		List	*lst = path[i].current;
		while (lst)
		{
			Vector2		*v = lst->content;
			Position	d_pos = (Position) {v->x * TILE_SZ, v->y * TILE_SZ};
			DrawRectangle(d_pos.x, d_pos.y, TILE_SZ, TILE_SZ, ColorAlpha(BLUE, 0.3));
			lst = lst->next;
		}
	}
}


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
	printf("start: %f,%f | target: %f, %f\n", start.x, start.y, target.x, target.y);
	if (_nodes_arena == NULL)
		_nodes_arena = arena_create_sized(sizeof(Node), map.size.x * map.size.y); // NOTE hard coded number
	else
		arena_clean(_nodes_arena);
	if (path->mem == NULL)
		path->mem = arena_create_sized(sizeof(List) + sizeof(Vector2), 10);
	else
		arena_clean(path->mem);
	Node	*target_node = a_star(start, target, map, _nodes_arena);

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
		lstadd_front(&path_lst, new);
		current = current->prev;
	}
	path->head = path_lst;
	path->current = path_lst;
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
				if (Vector2Compare(neighbor->pos, target)) // NOTE i dont remember why this check exists and the goto out
				{
					arena_destroy(arena_lst);
					return (neighbor);
					printf("aosnetuhaoestnuheoasntuh\n");
					goto out;
				}
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
	printf("a_star target not found, target: %f,%f\n", target.x, target.y);
	printf("map[target]: %d\n", get_array(map.arr, target));
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

#endif
