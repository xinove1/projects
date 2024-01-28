#include "game.h"
#include "../parson/parson.h"

#define FILE_PATH "ldtk/teste/simplified/Level_0/data.json"
#define LDTK_FILE_PATH "ldtk/teste.ldtk"

void	load_grid(ecs_world_t *world)
{
	JSON_Value	*root;
	JSON_Object	*root_obj;
	JSON_Array	*levels;

	root = json_parse_file(LDTK_FILE_PATH);
    if (json_value_get_type(root) != JSONObject) {
		printf("[ERROR] load_level: json file provided error\n");
	}
	root_obj = json_value_get_object(root);
	levels = json_object_get_array(root_obj, "levels");
	for (int i = 0; i < json_array_get_count(levels); i++)
	{
		JSON_Object	*level = json_array_get_object(levels, i);
		printf("Level id: %s\n", json_object_get_string(level, "identifier"));
		JSON_Array	*layer_instances = json_object_get_array(level, "layerInstances");
		for (int j = 0; j < json_array_get_count(layer_instances); j++)
		{
			JSON_Object	*layer = json_array_get_object(layer_instances, j);
			const char	*layer_id = json_object_get_string(layer, "__identifier");
			if (!strcmp(layer_id, "Tiles"))
			{
				JSON_Array	*grid = json_object_get_array(layer, "gridTiles");
				for (int k = 0; k < json_array_get_count(grid); k++)
				{
					JSON_Object	*grid_tile = json_array_get_object(grid, k);
					JSON_Array	*tmp;
					Position	pos;
					Tile		tile;
					tmp =  json_object_get_array(grid_tile, "src");
					tile.x = json_array_get_number(tmp, 0) / TILE_SZ;
					tile.y = json_array_get_number(tmp, 1) / TILE_SZ;
					if (tile.x == 0 && tile.y == 0) // NOTE currently using tranparent tilesheet, first tile is just tranparent
						continue;
					tmp =  json_object_get_array(grid_tile, "px");
					pos.x = json_array_get_number(tmp, 0) / TILE_SZ;
					pos.y = json_array_get_number(tmp, 1) / TILE_SZ;
					ecs_entity_t	new_tile = ecs_new_id(world);
					ecs_set(world, new_tile, Tile, {tile.x, tile.y});
					ecs_set(world, new_tile, Position, {pos.x, pos.y});
				}
			}
		}
	}
	json_value_free(root);
}

void	load_level(ecs_world_t *world)
{
	JSON_Value	*root;
	JSON_Object	*level;
	ecs_entity_t	game_map = ecs_lookup(world, "GameMap");

	root = json_parse_file(FILE_PATH);
    if (json_value_get_type(root) != JSONObject) {
		printf("[ERROR] load_level: json file provided error\n");
	}

	level = json_value_get_object(root);

	// Init map with game area from level
	{
		Vector2	map_bounds;
		map_bounds.x = json_object_get_number(level, "width");
		map_bounds.y = json_object_get_number(level, "height");
		Arr2D	*map = ecs_get_mut(world, game_map, Arr2D);
		if (!map->arr)
		{
			map->arr = calloc(map_bounds.y, sizeof(int *));
			for (int i = 0; i < map_bounds.y; i++)
				map->arr[i] = calloc(map_bounds.x, sizeof(int));
			map->size = map_bounds;
		}
	}
	// Init Enemy_test
	{
		JSON_Array	*enemys = json_object_dotget_array(level, "entities.Enemy_test");
		ecs_entity_t	player = ecs_lookup(world, "Player");
		for (int i = 0; i < json_array_get_count(enemys); i++)
		{
			JSON_Object	*enemy = json_array_get_object(enemys, i);
			JSON_Object	*components = json_object_get_object(enemy, "customFields");
			ecs_entity_t	e = ecs_new_id(world);
			{
				Position	pos;
				pos.x = json_object_dotget_number(enemy, "x") / TILE_SZ;
				pos.y = json_object_dotget_number(enemy, "y") / TILE_SZ;
				ecs_set(world, e, Position, {pos.x, pos.y});
			}
			if (json_object_dothas_value(components, "Collision"))
			{
				printf("collis\n");
				ecs_add(world, e, Collider);
			}
			if (json_object_dothas_value(components, "Path_find.To_player"))
			{
				printf("Path_find.To_player\n");
				ecs_set(world, e, Path, {NULL, NULL, NULL});
				ecs_add_pair(world, e, TargetFollow, player);
			}
			if (json_object_has_value(components, "Tile"))
			{
				Position	tile;
				tile.x = json_object_dotget_number(components, "Tile.x") / TILE_SZ;
				tile.y = json_object_dotget_number(components, "Tile.y") / TILE_SZ;
				ecs_set(world, e, Tile, {tile.x, tile.y});
			}
		}
	}

	/* arr = json_value_get_array(root_value); */
	/* int count = json_array_get_count(arr); */

	json_value_free(root);
}
