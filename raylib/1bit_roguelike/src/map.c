#include "game.h"

void	render_colliders_map(ecs_iter_t	*it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*arr = ecs_get(it->world, game_map, Arr2D);
	int	**map = *arr;
	if (map == NULL)
	{
		printf("Tryng to render a empty map \n");
		return ;
	}
	for (int y = 0; y < data.map_bounds.y; y++)
	{
		for (int x = 0; x < data.map_bounds.x; x++)
		{
			if (map[y][x] == 0)
				continue;
			Position	d_pos = (Position) {x * TILE_SZ, y * TILE_SZ};
			DrawRectangle(d_pos.x, d_pos.y, TILE_SZ, TILE_SZ, ColorAlpha(RED, 0.3));
		}
	}
}

void	render_pathfind(ecs_iter_t *it)
{
	Path	*path = ecs_field(it, Path, 1);

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

void	on_new_collider(ecs_iter_t *it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	fill_map(it->world, it->ctx, game_map);
}

void	fill_map(ecs_world_t *world, ecs_query_t	*colliders, ecs_entity_t	game_map)
{
	Arr2D	*arr = ecs_get_mut(world, game_map, Arr2D);
	int	**map = *arr;
	if (!map)
	{
		map = calloc(data.map_bounds.y, sizeof(int *));
		for (int i = 0; i < data.map_bounds.y; i++)
			map[i] = calloc(data.map_bounds.x, sizeof(int));
		*arr = map;
	}
	else
	{
		for (int y = 0; y < data.map_bounds.y; y++)
		{
			for (int x = 0; x < data.map_bounds.x; x++)
				map[y][x] = 0;
		}
	}
	Position	bounds = (Position) {data.map_bounds.x, data.map_bounds.y};
	ecs_iter_t	iter = ecs_query_iter(world, colliders);
	while (ecs_query_next(&iter))
	{
		Position	*pos = ecs_field(&iter, Position, 1);
		for (int i = 0; i < iter.count; i++)
		{
			if (pos[i].x >= 0 && pos[i].x < bounds.x && pos[i].y >= 0 && pos[i].y < bounds.y)
				map[pos[i].y][pos[i].x] = 1;
			map[0][0] = 1;
		}
	}
}
