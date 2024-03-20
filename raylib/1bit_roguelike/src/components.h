#ifndef COMPONENTS_H
# define COMPONENTS_H
# include "includes.h"
# include "modules.h"

typedef enum
{
	PATROL,
	FOLLOW,
} BASIC_ENEMY_STATES;

typedef BASIC_ENEMY_STATES EnemyState;
typedef int	LineOfSight;

typedef int Health;
typedef float TimerDeath;

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
} Attack; // TODO remove


// Components
extern ECS_COMPONENT_DECLARE(Tile);
extern ECS_COMPONENT_DECLARE(Health);
extern ECS_COMPONENT_DECLARE(FlashColor);
extern ECS_COMPONENT_DECLARE(Attack);
extern ECS_COMPONENT_DECLARE(TimerDeath);
extern ECS_COMPONENT_DECLARE(EnergyLevel);
extern ECS_COMPONENT_DECLARE(EnemyState);
extern ECS_COMPONENT_DECLARE(LineOfSight);

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


#endif // COMPONENT_H_
