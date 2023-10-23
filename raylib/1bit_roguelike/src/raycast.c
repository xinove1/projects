#include "game.h"

// TODO clean from debug stuff
Vector2	raycast(Vector2 origin, Vector2 dir, int lenght, int **map)
{
	Vector2	step_size = {sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x)), sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y))};
	/* Vector2	step_size = {sqrt(1 + (dir.y * dir.y) / (dir.x / dir.x)), sqrt(1 + (dir.x * dir.x) / (dir.y * dir.y))}; */
	Vector2	current = {(int) origin.x, (int) origin.y}; // Chunking to specific tile if origin is pos inside a tile
	Vector2	raylenght;
	Vector2	step_dir;

	if (dir.x < 0)
	{
		step_dir.x = -1;
		raylenght.x = (origin.x - current.x) * step_size.x;
	}
	else
	{
		step_dir.x = 1;
		raylenght.x = ((current.x + 1) - origin.x) * step_size.x;
	}
	if (dir.y < 0)
	{
		step_dir.y = -1;
		raylenght.y = (origin.y - current.y) * step_size.y;
	}
	else
	{
		step_dir.y = 1;
		raylenght.y = ((current.y + 1) - origin.y) * step_size.y;
	}
	/* printf("-----------------------\n"); */
	/* printf("origin: %f,%f\n", origin.x, origin.y); */
	/* printf("dir: %f,%f\n", dir.x, dir.y); */
	/* printf("step_size: %f,%f\n", step_size.x, step_size.y); */
	/* printf("current: %f,%f\n", current.x, current.y); */
	/* printf("raylenght: %f,%f\n", raylenght.x, raylenght.y); */
	/* printf("step_dir: %f,%f\n", step_dir.x, step_dir.y); */
	float	distance = 0;
	while (distance < lenght)
	{
		if (raylenght.x < raylenght.y)
		{
			current.x += step_dir.x;
			distance = raylenght.x;
			raylenght.x += step_size.x;
		}
		else
		{
			current.y += step_dir.y;
			distance = raylenght.y;
			raylenght.y += step_size.y;
		}
		Position	icurrent = Vector2ToPos(current);
		if (icurrent.x < 0 || icurrent.x >= data.map_bounds.x || icurrent.y < 0 || icurrent.y >= data.map_bounds.y)
			break ;
		//printf("icurrent: %d,%d\n", icurrent.x, icurrent.y);
		{
			/* ecs_entity_t	t = ecs_new_id(data.ecs); */
			/* ecs_set(data.ecs, t, Position, {icurrent.x, icurrent.y }); */
			/* ecs_set(data.ecs, t, Tile, {50}); */
			/* ecs_set(data.ecs, t, TimerDeath, {4}); */
		}
		if (map[icurrent.y][icurrent.x] == 1)
		{
			Vector2 r = Vector2Add(origin, Vector2Scale(dir, distance));
			/* printf("distance %f\n", distance); */
			/* printf("r: %f,%f\n", r.x, r.y); */
			return (r);
		}
	}
	return (Vector2Zero());
}

ecs_entity_t	*raycast_entity(Vector2 origin, Vector2 dir, int lenght, ecs_query_t *entitys, ecs_world_t *world)
{
	Vector2	step_size = {sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x)), sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y))};
	Vector2	current = {(int) origin.x, (int) origin.y};
	Vector2	raylenght;
	Vector2	step_dir;

	if (dir.x < 0)
	{
		step_dir.x = -1;
		raylenght.x = (origin.x - current.x) * step_size.x;
	}
	else
	{
		step_dir.x = 1;
		raylenght.x = ((current.x + 1) - origin.x) * step_size.x;
	}
	if (dir.y < 0)
	{
		step_dir.y = -1;
		raylenght.y = (origin.y - current.y) * step_size.y;
	}
	else
	{
		step_dir.y = 1;
		raylenght.y = ((current.y + 1) - origin.y) * step_size.y;
	}

	float	distance = 0;
	while (distance < lenght)
	{
		if (raylenght.x < raylenght.y)
		{
			current.x += step_dir.x;
			distance = raylenght.x;
			raylenght.x += step_size.x;
		}
		else
		{
			current.y += step_dir.y;
			distance = raylenght.y;
			raylenght.y += step_size.y;
		}
		Position	icurrent = Vector2ToPos(current);
		if (icurrent.x < 0 || icurrent.x >= data.map_bounds.x || icurrent.y < 0 || icurrent.y >= data.map_bounds.y)
			break ;
		ecs_entity_t	*entity = check_collision(icurrent, entitys, world);
		if (entity)
			return (entity);
	}
	return (NULL);
}
