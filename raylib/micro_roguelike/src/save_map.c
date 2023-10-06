#include "game.h"

/* int	save_map(GameMap map, char *file_name) */
/* { */
/* 	int	data_size = sizeof(Vector2) + (map.size.x * sizeof(GameTile)) + (map.size.y * sizeof(GameTile*)); */
/* 	printf("sizeof given map: %d\n", data_size); */
/* 	SaveFileData(file_name, &map, data_size); */
/* 	return (1); */
/* } */

/* int	load_map(GameMap *map, char *file_name) */
/* { */
/* 	int	data_read; */
/* 	unsigned char *data = LoadFileData(file_name, &data_read); */
/* 	printf("data_read: %d\n", data_read); */
/* 	Vector2 map_size = ((Vector2 *)data)[0]; */
/* 	printf("map size read: %f,%f\n", map_size.x, map_size.y); */
/* 	data += sizeof(Vector2); */
/* 	GameTile	*mapp = ((GameTile **)data)[0]; */
/* 	printf("mapp.tile: %d\n", mapp->tile); */
/* 	//map->map = mapp; */
/* 	return (1); */
/* } */
