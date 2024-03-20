#include "game.h"

static List	*lstfind_pos(List *list, Vector2 *content);
static Vector2	**get_neighbors(Arena *arena, Arr2D grid, Vector2 pos);

void	pathfind(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Path		*path = ecs_field(it, Path, 2);
	const Arr2D	*map = ecs_get(it->world, ecs_lookup(it->world, "GameMap"), Arr2D);

	for (int i = 0; i < it->count; i++)
	{
		ecs_entity_t	target_entity = ecs_get_target(it->world, it->entities[i], TargetFollow, 0);
		const Position	*target_pos = ecs_get(it->world, target_entity, Position);
		/* const Position	*target_pos = &(Position){pos[i].x - 3, pos[i].y - 3}; */
		//Position	*target = (Position *) ecs_field(it, Target, 2);
		/* if (!IsKeyPressed(KEY_M)) */
		/* 	return ; */
		if (path[i].mem == NULL)
			path[i].mem = arena_create_sized(sizeof(List) + sizeof(Vector2), 10);
		arena_clean(path[i].mem);
		pathfind_a_star(&path[i], PosToVector2(pos[i]), PosToVector2(*target_pos), *map);
		Vector2 current = *(Vector2 *)path[i].current->content;
		printf("path.current %f,%f\n", current.x, current.y);
	}
}

List	*pathfind_breadth_first(Arena *arena, Arena *scratch, Arr2D grid, Vector2 grid_size, Vector2 starting_pos, Vector2 goal)
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
		Vector2	**adjecents = get_neighbors(scr, grid, current); // NOTE does not actually need to be a pointer, maybe refactor
		int		i = -1;
		while (adjecents[++i])
		{
			if (lstfind_pos(reached, adjecents[i]) == NULL && (get_array(grid.arr, *adjecents[i]) == 0 || Vector2Compare((Vector2) {goal.x, goal.y}, *adjecents[i])))
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

static Vector2	**get_neighbors(Arena *arena, Arr2D grid, Vector2 pos)
{
	Vector2	**neighbors = linear_alloc(arena, 5 * sizeof(Vector2 *));
	Vector2	add[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int		i = -1;
	int		k = 0;

	while (++i < 4)
	{
		Vector2	new_pos = Vector2Add(pos, add[i]);
		if (new_pos.x < 0 || new_pos.x >= grid.size.x || new_pos.y < 0 || new_pos.y >= grid.size.y)
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
