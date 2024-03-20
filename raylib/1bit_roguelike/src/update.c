#include "game.h"

void	test_raycast(ecs_iter_t	*it)
{

	Vector2	mouse_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
	Vector2	mouse_pos_tiled = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
	mouse_pos_tiled = Vector2Divide(mouse_pos, (Vector2){TILE_SZ, TILE_SZ});
	DrawText(TextFormat("%f,%f", mouse_pos_tiled.x, mouse_pos_tiled.y), mouse_pos.x, mouse_pos.y - 10, 5, PURPLE);
	DrawCircle(mouse_pos.x, mouse_pos.y, 2, BLUE);

	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*map = ecs_get(it->world, game_map, Arr2D);

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		ecs_entity_t	tile = ecs_new_id(it->world);
		Position pos = Vector2ToPos(mouse_pos_tiled);
		ecs_set(it->world, tile, Position, {pos.x, pos.y});
		ecs_set(it->world, tile, Tile, {19, 1});
		ecs_add(it->world, tile, Collider);
	}
	if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
	{
		Position pos = Vector2ToPos(mouse_pos_tiled);
		ecs_entity_t	*tile = check_collision(pos, it->world);
		if (tile)
			ecs_delete(it->world, *tile);
	}
	static Vector2 pos = {0};
	static Vector2 target = {0};
	if (IsKeyDown(KEY_X))
	{
		ecs_entity_t	player = ecs_lookup(it->world, "Player");
		const Position	* pos_p =ecs_get(it->world, player, Position);
		pos = PosToVector2(*pos_p);
		ecs_entity_t	*e = raycast_entity((Vector2) {pos.x, pos.y}, Vector2Normalize(Vector2Subtract(mouse_pos_tiled, pos)), 10, it->world);
		if (e)
			ecs_delete(it->world, *e);
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	/* if (IsKeyPressed(KEY_Q)) */
	{
		ecs_entity_t	player = ecs_lookup(it->world, "Player");
		const Position	* pos_p =ecs_get(it->world, player, Position);
		pos = PosToVector2(*pos_p);
		pos = (Vector2) {pos.x + 0.5f, pos.y + 0.5f};
		target = raycast((Vector2) {pos.x, pos.y}, Vector2Normalize(Vector2Subtract(mouse_pos_tiled, pos)), 10, *map);
	}
	if (Vector2Compare(target,  Vector2Zero()))
		DrawLine(pos.x * TILE_SZ, pos.y * TILE_SZ, mouse_pos.x, mouse_pos.y, GREEN);
	else
		DrawLine(pos.x * TILE_SZ, pos.y * TILE_SZ , target.x * TILE_SZ, target.y * TILE_SZ, GREEN);

}

void	tick_deathtimer(ecs_iter_t *it)
{
	TimerDeath	*timer = ecs_field(it, TimerDeath, 1);

	for (int i = 0; i < it->count; i++)
	{
		timer[i] -= it->delta_time;
		if (timer[i] <= 0)
			ecs_delete(it->world, it->entities[i]);
	}
}

void	game_loop(ecs_iter_t	*it)
{

	bool	*player_action_wait = ecs_get_mut(it->world, ecs_lookup(it->world, "PlayerAction"), Bool);
	if (*player_action_wait)
		return ;
	printf("it->count %d\n", it->count);
	ecs_iter_t	query = ecs_query_iter(it->world, it->ctx);
	printf("it->count %d\n", it->count);
	while (ecs_query_next(&query))
	{
	EnergyLevel	*energy = ecs_field(&query, EnergyLevel, 1);
	for (int i = 0; i < query.count; i++)
	{
		printf("loop %d\n", i);
		energy[i].current += energy[i].increment;
		if (energy[i].current >= ENERGY_THRESHOLD)
		{
			//printf("entity energy: %s, %d\n", ecs_get_name(query.world, query.entities[i]), energy[i].current);
			//printf("%d\n", energy[i].current);
			if (ecs_has_id(query.world, query.entities[i], Player))
			{
				*player_action_wait = true;
			}
			else
			{
				printf("enemy turn\n");
				basic_enemy_state_machine(&query.entities[i], query.world);
				//WaitTime(5);
			}
			energy[i].current -= ENERGY_THRESHOLD;
		}
	}
	}
	printf("exiting loop\n");
}

void	input_player(ecs_iter_t *it)
{
	bool	*player_action_wait = ecs_get_mut(it->world, ecs_lookup(it->world, "PlayerAction"), Bool);
	if (!*player_action_wait)
		return ;
	ecs_entity_t	player = ecs_lookup(it->world, "Player");
	Dir		*dir = ecs_get_mut(it->world, player, Dir);

	if (IsKeyPressed(KEY_A))
		dir->x = -1;
	else if (IsKeyPressed(KEY_D))
		dir->x = 1;
	else if (IsKeyPressed(KEY_W))
		dir->y = -1;
	else if (IsKeyPressed(KEY_S))
		dir->y = 1;
	if (dir->x != 0 || dir->y != 0)
	{
		*player_action_wait = false;
		ecs_entity_t	*e = move(*dir, &player, it->world);
		if (e && ecs_has_id(it->world, *e, ecs_id(Health)))
			attack(1, e, it->world);
		dir->x = 0;
		dir->y = 0;
	}
}

void	camera_follow_player(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);

	data.camera.target = (Vector2) {pos[0].x * TILE_SZ, pos[0].y * TILE_SZ};
	//data.camera.offset = (Vector2) {pos[0].x * TILE_SZ / 2, pos[0].y * (TILE_SZ / 2)};
}

void	despawn(ecs_iter_t *it)
{
	for (int i = 0; i < it->count; i++)
	{
		printf("Entity died\n");
		ecs_delete(it->world, it->entities[i]);
	}
}

ecs_entity_t	*check_collision(Position target, ecs_world_t *it_world)
{
	return (check_entitys(target, COLLIDERS_QUERY, it_world));
}

// TODO Rename
ecs_entity_t	*check_entitys(Position target, ecs_query_t *colliders_query, ecs_world_t *it_world)
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
