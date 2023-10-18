#include "game.h"

void	pathfind_build(Path *path, int **map, Vector2 start_pos, Vector2 target);
static List	*lstfind_pos(List *list, Vector2 *content);
static Vector2	**get_neighbors(Arena *arena, int **grid, Vector2 grid_size, Vector2 pos);

void	pathfind(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Path		*path = ecs_field(it, Path, 2);
	const Arr2D	*arr = ecs_get(it->world, ecs_lookup(it->world, "GameMap"), Arr2D);
	int	**map = *arr;

	for (int i = 0; i < it->count; i++)
	{
		ecs_entity_t	target_entity = ecs_get_target(it->world, it->entities[i], TargetFollow, 0);
		const Position	*target_pos = ecs_get(it->world, target_entity, Position);
		/* const Position	*target_pos = &(Position){pos[i].x - 3, pos[i].y - 3}; */
		//Position	*target = (Position *) ecs_field(it, Target, 2);
		if (!IsKeyPressed(KEY_M))
			return ;
		printf("AAA\n");
		if (path[i].memL == NULL)
			path[i].memL = arena_create_sized(0, 4);
		if (path[i].memV == NULL)
			path[i].memV = arena_create_sized(0, 5);
		arena_clean(path[i].memV);
		arena_clean(path[i].memL);
		pathfind_build(&path[i], map, (Vector2) {pos[i].x, pos[i].y}, (Vector2) {target_pos->x, target_pos->y});
		//ecs_remove(it->world, it->entities[i], Target);
	}
}

void	pathfind_build(Path *path, int **map, Vector2 start_pos, Vector2 target)
{
	Arena	*scratch = arena_create_sized(sizeof(List), 20);
	List	*list = pathfind_breadth_first(path->memV, scratch, map, data.map_bounds, start_pos, target);
	List	*current_node = lstfind_pos(list, &target);
	List	*path_list = lstnew(path->memL, current_node->content);

	while (current_node)
	{
		Vector2	from = ((Vector2 *)current_node->content)[1];
		Vector2	current = ((Vector2 *)current_node->content)[0];
		lstadd_front(&path_list, lstnew(path->memL, current_node->content));
		if (from.x == -1)
			break ;
		current_node = lstfind_pos(list, &from);
	}
	arena_destroy(scratch);
	path->current = path_list;
	path->head = path_list;
}


List	*pathfind_breadth_first(Arena *arena, Arena *scratch, int **grid, Vector2 grid_size, Vector2 starting_pos, Vector2 goal)
{
	Vector2	*pos = linear_alloc(arena, sizeof(Vector2));
	*pos = (Vector2) {starting_pos.x, starting_pos.y};
	List	*frontier = lstnew(scratch, pos);
	Vector2	*p = linear_alloc(arena, 2 * sizeof(Vector2));

	p[0] = *pos;
	p[1] = (Vector2) {-1, -1};
	List	*reached = lstnew(scratch, p);

	Arena	*scr = arena_create(0);
	while (frontier)
	{
		Vector2	current = *((Vector2 *) frontier->content);
		if (current.x == goal.x && current.y == goal.y)
			break ;
		Vector2	**adjecents = get_neighbors(scr, grid, grid_size, current); // NOTE does not actually need to be a pointer, maybe refactor
		int		i = -1;
		while (adjecents[++i])
		{
			if (lstfind_pos(reached, adjecents[i]) == NULL && (get_array(grid, *adjecents[i]) == 0 || Vector2Compare((Vector2) {goal.x, goal.y}, *adjecents[i])))
			{
				Vector2	*a = linear_alloc(arena, 2 * sizeof(Vector2));
				a[0] = *adjecents[i];
				a[1] = *((Vector2 *) frontier->content);
				lstadd_back(&frontier, lstnew(scratch, a));
				lstadd_back(&reached, lstnew(scratch, a));
			}
		}
		arena_clean(scr);
		List	*ref = frontier;
		frontier = frontier->next;
		pool_free(scratch, ref);
	}
	arena_destroy(scr);
	return (reached);
}

static Vector2	**get_neighbors(Arena *arena, int **grid, Vector2 grid_size, Vector2 pos)
{
	Vector2	**neighbors = linear_alloc(arena, 5 * sizeof(Vector2 *));
	Vector2	add[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int		i = -1;
	int		k = 0;

	while (++i < 4)
	{
		Vector2	new_pos = Vector2Add(pos, add[i]);
		if (new_pos.x < 0 || new_pos.x >= grid_size.x || new_pos.y < 0 || new_pos.y >= grid_size.y)
			continue ;
		Vector2	*neighbor = linear_alloc(arena, sizeof(Vector2));
		*neighbor = new_pos;
		neighbors[k] = neighbor;
		k++;
	}
	return (neighbors);
}

static List	*lstfind_pos(List *list, Vector2 *content)
{
	while (list)
	{
		Vector2	*v = (Vector2 *)list->content;
		if (v->x == content->x && v->y == content->y)
			return (list);
		list = list->next;
	}
	return (NULL);
}
