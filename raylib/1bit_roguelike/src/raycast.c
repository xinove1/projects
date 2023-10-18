#include "game.h"

Vector2	raycast(Vector2 origin, Vector2 dir, int lenght, int **map)
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
		if (icurrent.x < 0 || icurrent.x >= data.map_bounds.x || icurrent.y < 0 || icurrent.y >= data.map_bounds.y)
			break ;
		printf("icurrent: %d,%d\n", icurrent.x, icurrent.y);
		if (map[icurrent.y][icurrent.x] == 1)
		{
			printf("bsA\n");
			Vector2 r =Vector2Add(origin, Vector2Scale(step_dir, distance));
			printf("r: %f,%f\n", r.x, r.y);
			return (r);
		}
	}
	return (Vector2Zero());
}
