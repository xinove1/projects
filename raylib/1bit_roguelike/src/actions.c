#include "game.h"

static ecs_entity_t	*raycast_line_sight(Vector2 origin, int lenght, ecs_world_t *ecs)
{
	Vector2	dir = {0, 0};
	origin = Vector2Add(origin, (Vector2){0.5, 0.5}); // Cast ray from middle of tile instead of  corner
	for (int angle = 0; angle < 360; angle += 10)
	{
		dir = (Vector2) {cos(DEG2RAD * angle), sin(DEG2RAD * angle)};
		ecs_entity_t *e = raycast_entity(origin, dir, lenght, ecs);
		if (e && ecs_has_id(ecs, *e, ecs_id(Player)))
			return (e);
	}
	return (NULL);
}

void	basic_enemy_state_machine(ecs_entity_t *enemy, ecs_world_t *ecs)
{
	EnemyState	state = *ecs_get(ecs, *enemy, EnemyState);
	if (state == PATROL)
	{
		LineOfSight	sight_lenght = *ecs_get(ecs, *enemy, LineOfSight);
		Position	pos = *ecs_get(ecs, *enemy, Position);
		ecs_entity_t	*e = raycast_line_sight(PosToVector2(pos), sight_lenght, ecs);
		if (e)
		{
			{
				Path	*path = ecs_get_mut(ecs, *enemy, Path);
				ecs_entity_t	game_map = ecs_lookup(ecs, "GameMap");
				ecs_entity_t	player = ecs_lookup(ecs, "Player");
				Position player_pos = *ecs_get(ecs, player, Position);
				Position enemy_pos = *ecs_get(ecs, *enemy, Position);
				pathfind_a_star(path, PosToVector2(enemy_pos), PosToVector2(player_pos), *ecs_get(ecs, game_map, Arr2D));
			}
			ecs_set(ecs, *enemy, EnemyState, {FOLLOW});
		}
	}
	else if (state == FOLLOW)
	{
		Path	*path = ecs_get_mut(ecs, *enemy, Path);
		Vector2	dir = next_path_dir(path);
		if (dir.x == 0 && dir.y == 0)
		{
			ecs_set(ecs, *enemy, EnemyState, {PATROL});
			return ;
		}
		ecs_entity_t	*e = move(dir, enemy, ecs);
		if (e)
			attack(1, e, ecs);
	}
}

ecs_entity_t	*move_to_pos(Vector2 pos, ecs_entity_t *e, ecs_world_t *ecs)
{
	ecs_entity_t	*collider = check_collision(Vector2ToPos(pos), ecs);
	if (collider)
		return (collider);
	ecs_set(ecs, *e, Position, {pos.x, pos.y});
	return (NULL);
}

ecs_entity_t	*move(Vector2 dir, ecs_entity_t *e, ecs_world_t *ecs)
{
	if (dir.x == 0 && dir.y == 0)
		return (NULL);
	Position	pos = * ecs_get(ecs, *e, Position);
	Position	new_pos;
	new_pos.x = pos.x + dir.x;
	new_pos.y = pos.y + dir.y;
	ecs_entity_t	*collider = check_collision(new_pos, ecs);
	if (collider)
		return (collider);
	ecs_set(ecs, *e, Position, {new_pos.x, new_pos.y});
	return (NULL);
}

void	attack(int damage, ecs_entity_t *target, ecs_world_t *ecs)
{
	if (!ecs_has_id(ecs, *target, ecs_id(Health)))
		return ;
	Health	health = * ecs_get(ecs, *target, Health);
	ecs_set(ecs, *target, Health, {health - damage});
	ecs_set(ecs, *target, FlashColor, {0.1f, 0, RED});
	if (health - damage <= 0) // TODO move to observer on set health
		ecs_add(ecs, *target, Despawn);
}
