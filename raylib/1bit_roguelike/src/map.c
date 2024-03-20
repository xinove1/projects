#include "game.h"

void	update_colliders_map(ecs_iter_t *it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");

	fill_map(it->world, COLLIDERS_QUERY, game_map);
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

void	place_game_border(ecs_world_t *world)
{
	const int	TILE = 50;
	for (int i = 0; i <= data.map_bounds.y; i++)
	{
		ecs_entity_t	wall = ecs_new_id(world);
		ecs_set(world, wall, Position, {-1, i});
		ecs_set(world, wall, Tile, {TILE});
		ecs_add(world, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.y; i++)
	{
		ecs_entity_t	wall = ecs_new_id(world);
		ecs_set(world, wall, Position, {data.map_bounds.x, i});
		ecs_set(world, wall, Tile, {TILE});
		ecs_add(world, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.x; i++)
	{
		ecs_entity_t	wall = ecs_new_id(world);
		ecs_set(world, wall, Position, {i, -1});
		ecs_set(world, wall, Tile, {TILE});
		ecs_add(world, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.x; i++)
	{
		ecs_entity_t	wall = ecs_new_id(world);
		ecs_set(world, wall, Position, {i, data.map_bounds.y });
		ecs_set(world, wall, Tile, {TILE});
		ecs_add(world, wall, Collider);
	}
}
