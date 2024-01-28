#ifndef COMPONENTS_H
# define COMPONENTS_H
# include "../../../../raylib/src/raylib.h"
# include "../flecs/flecs.h"
# include "../../../mylibc/libft.h"

typedef struct
{
	int	x;
	int	y;
} Vector2Int;

typedef Vector2Int Position;
typedef Vector2	Dir;

typedef bool Bool;
typedef int Health;
typedef float TimerDeath;

typedef struct
{
	int	**arr;
	Vector2	size;
} Arr2D;

typedef struct
{
	Arena	*mem;
	List	*head;
	List	*current;
} Path;

typedef struct
{
	int	current;
	int	increment;
}EnergyLevel;


typedef Vector2Int Tile;

typedef struct
{
	float	duration;
	float	timer;
	Color	color;
} FlashColor;

typedef struct
{
	Position	target;
	int			damage;
} Attack;


// Components
extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Tile);
extern ECS_COMPONENT_DECLARE(Health);
extern ECS_COMPONENT_DECLARE(Dir);
extern ECS_COMPONENT_DECLARE(FlashColor);
extern ECS_COMPONENT_DECLARE(Attack);
extern ECS_COMPONENT_DECLARE(Arr2D);
extern ECS_COMPONENT_DECLARE(Path);
extern ECS_COMPONENT_DECLARE(TimerDeath);
extern ECS_COMPONENT_DECLARE(EnergyLevel);
extern ECS_COMPONENT_DECLARE(Bool);

// Tags
extern ECS_TAG_DECLARE(Despawn);
extern ECS_TAG_DECLARE(Player);
extern ECS_TAG_DECLARE(Enemy);
extern ECS_TAG_DECLARE(Collider);
extern ECS_TAG_DECLARE(Despawn);
extern ECS_TAG_DECLARE(TargetFollow);

// Systems
//extern ECS_SYSTEM_DECLARE(id);

// Querys
extern ecs_query_t	*COLLIDERS_QUERY;
extern ecs_query_t	*COLLIDERS_HEALTH_QUERY;

// Ids
extern ECS_DECLARE(PreUpdate);
extern ECS_DECLARE(OnUpdate);
extern ECS_DECLARE(OnUpdateReal);
extern ECS_DECLARE(PostUpdate);
extern ECS_DECLARE(PreDraw);
extern ECS_DECLARE(PreDraw2D);
extern ECS_DECLARE(OnDraw2D);
extern ECS_DECLARE(PostDraw2D);
extern ECS_DECLARE(OnDraw);
extern ECS_DECLARE(PostDraw);

#endif // COMPONENT_H_
