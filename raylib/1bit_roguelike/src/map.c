#include "game.h"

void	on_new_collider(ecs_iter_t *it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	fill_map(it->world, it->ctx, game_map);
}

void	fill_map(ecs_world_t *world, ecs_query_t	*colliders, ecs_entity_t	game_map)
{
	Arr2D	*map = ecs_get_mut(world, game_map, Arr2D);
	if (!map->arr)
	{
		map->arr = calloc(data.map_bounds.y, sizeof(int *));
		for (int i = 0; i < data.map_bounds.y; i++)
			map->arr[i] = calloc(data.map_bounds.x, sizeof(int));
		map->size = data.map_bounds;
		//*arr = map;
	}
	else
	{
		for (int y = 0; y < data.map_bounds.y; y++)
		{
			for (int x = 0; x < data.map_bounds.x; x++)
				map->arr[y][x] = 0;
		}
	}

	ecs_iter_t	iter = ecs_query_iter(world, colliders);
	while (ecs_query_next(&iter))
	{
		Position	*pos = ecs_field(&iter, Position, 1);
		for (int i = 0; i < iter.count; i++)
		{
			if (pos[i].x >= 0 && pos[i].x < map->size.x && pos[i].y >= 0 && pos[i].y < map->size.y)
				map->arr[pos[i].y][pos[i].x] = 1;
		}
	}
}
