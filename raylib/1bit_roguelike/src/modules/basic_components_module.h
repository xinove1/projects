#ifndef BASIC_COMPONENTS_MODULE_H_
# define BASIC_COMPONENTS_MODULE_H_

# include "../includes.h"

typedef struct
{
	int	x;
	int	y;
} Vector2Int;

// TODO teste if this can easy changed back to Vector2
typedef Vector2Int Position;

typedef Vector2	Dir;
typedef struct
{
	int	**arr;
	Vector2	size;
} Arr2D;

typedef bool Bool;

void	BasicComponentsImport(ecs_world_t *ecs);
Position	Vector2ToPos(Vector2 v);
Vector2		PosToVector2(Position p);

extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Dir);
extern ECS_COMPONENT_DECLARE(Arr2D);
extern ECS_COMPONENT_DECLARE(Bool);

#endif // BASIC_COMPONENTS_MODULE_H_

#ifdef BASIC_COMPONENTS_MODULE_IMPLEMENTATION

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Bool);
ECS_COMPONENT_DECLARE(Dir);
ECS_COMPONENT_DECLARE(Arr2D);

void	BasicComponentsImport(ecs_world_t *ecs)
{
	ECS_MODULE(ecs, BasicComponents);
	ECS_COMPONENT_DEFINE(ecs, Position);
	ECS_COMPONENT_DEFINE(ecs, Bool);
	ECS_COMPONENT_DEFINE(ecs, Arr2D);
	ECS_COMPONENT_DEFINE(ecs, Dir);
}

Position	Vector2ToPos(Vector2 v)
{
	return ((Position) {v.x, v.y});
}

Vector2		PosToVector2(Position p)
{
	return ((Vector2) {p.x, p.y});
}

int	get_array(int	**array, Vector2 pos)
{
	return (array[(int)pos.y][(int)pos.x]);
}

void	set_array(int	**array, Vector2 pos, int new_value)
{
	array[(int)pos.y][(int)pos.x] = new_value;
}

int	Vector2Compare(Vector2 vec1, Vector2 vec2) // NOTE rename?
{
	return (vec1.x == vec2.x &&  vec1.y == vec2.y);
}

#endif
