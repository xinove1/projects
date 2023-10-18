#include "game.h"

ecs_entity_t	*check_collision(Position target, ecs_query_t *colliders_query, ecs_world_t *it_world);

void	input_player(ecs_iter_t *it)
{
	Dir	*dir = ecs_field(it, Dir, 1);

	if (IsKeyPressed(KEY_A))
		dir[0].x = -1;
	else if (IsKeyPressed(KEY_D))
		dir[0].x = 1;
	else if (IsKeyPressed(KEY_W))
		dir[0].y = -1;
	else if (IsKeyPressed(KEY_S))
		dir[0].y = 1;
}

void	camera_follow_player(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);

	data.camera.target = (Vector2) {pos[0].x * TILE_SZ, pos[0].y * TILE_SZ};
	//data.camera.offset = (Vector2) {pos[0].x * TILE_SZ / 2, pos[0].y * (TILE_SZ / 2)};
}
void	move(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Dir	*dir = ecs_field(it, Dir, 2);
	ecs_query_t	*colliders = it->ctx;

	for (int i = 0; i < it->count; i++)
	{
		if (dir[i].x == 0 && dir[i].y == 0)
			continue;
		Position	new_pos;
		new_pos.x = pos[i].x + dir[i].x;
		new_pos.y = pos[i].y + dir[i].y;
		ecs_entity_t	*collider = check_collision(new_pos, colliders, it->world);
		if (collider)
			ecs_set(it->world, it->entities[i], Attack, {new_pos, 2});
		else
			pos[i] = new_pos;
		dir[i] = (Vector2){0};
	}
}

void	attack(ecs_iter_t *it)
{
	Attack	*attack = ecs_field(it, Attack, 1);
	ecs_query_t	*colliders = it->ctx;

	for (int i = 0; i < it->count; i++)
	{
		ecs_entity_t	*collider = check_collision(attack[i].target, colliders, it->world);
		if (collider)
		{
			Health	*health = ecs_get_mut(it->world, *collider, Health);
			*health -= attack[i].damage;
			if (*health <= 0)
				ecs_add(it->world, *collider, Despawn);
			ecs_set(it->world, *collider, FlashColor, {0.1f, 0, RED});
		}
		ecs_remove(it->world, it->entities[i], Attack);
	}
}

void	despawn(ecs_iter_t *it)
{
	for (int i = 0; i < it->count; i++)
	{
		printf("entity died\n");
		ecs_delete(it->world, it->entities[i]);
	}
}

// TODO better names
ecs_entity_t	*check_collision(Position target, ecs_query_t *colliders_query, ecs_world_t *it_world)
{
	ecs_iter_t query = ecs_query_iter(it_world, colliders_query);
	while (ecs_query_next(&query))
	{
		Position	*pos =  ecs_field(&query, Position, 1);
		for (int i = 0; i < query.count; i++)
		{
			if (pos[i].x == target.x && pos[i].y == target.y)
				return (&query.entities[i]);
		}
	}
	return (NULL);
}
