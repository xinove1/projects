#ifndef RAYCAST_MODULE_H_
# define RAYCAST_MODULE_H_
# include "../includes.h"
# include "basic_components_module.h"

Vector2	raycast(Vector2 origin, Vector2 dir, int lenght, Arr2D map);
ecs_entity_t	*raycast_entity(Vector2 origin, Vector2 dir, int lenght, ecs_world_t *ecs);
void	set_raycast_entity_check_func(ecs_entity_t *(*check_collision)(Position, ecs_world_t*));
int		Vector2Compare(Vector2 vec1, Vector2 vec2);// NOTE rename?
int		get_array(int	**array, Vector2 pos);
void	set_array(int	**array, Vector2 pos, int new_value);

#endif // RAYCAST_MODULE_H_
#ifdef RAYCAST_MODULE_IMPLEMENTATION

static ecs_entity_t *(*_check_collision)(Position, ecs_world_t*) = NULL;

void	set_raycast_entity_check_func(ecs_entity_t *(*check_collision)(Position, ecs_world_t*))
{
	_check_collision = check_collision;
}

Vector2	raycast(Vector2 origin, Vector2 dir, int lenght, Arr2D map)
{
	Vector2	step_size = {sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x)), sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y))};
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
		if (icurrent.x < 0 || icurrent.x >= map.size.x || icurrent.y < 0 || icurrent.y >= map.size.y)
			break ;
		if (map.arr[icurrent.y][icurrent.x] == 1)
		{
			Vector2 r = Vector2Add(origin, Vector2Scale(dir, distance));
			return (r);
		}
	}
	return (Vector2Zero());
}

ecs_entity_t	*raycast_entity(Vector2 origin, Vector2 dir, int lenght, ecs_world_t *ecs)
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
		/* if (icurrent.x < 0 || icurrent.x >= map.size.x || icurrent.y < 0 || icurrent.y >= map.size.y) */
		/* 	break ; */
		assert(_check_collision != NULL);
		ecs_entity_t	*entity = (*_check_collision)(icurrent, ecs);
		if (entity)
			return (entity);
	}
	return (NULL);
}

#endif // RAYCAST_MODULE_IMPLEMENTATION
