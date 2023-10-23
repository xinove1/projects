#include "game.h"

void	test_raycast(ecs_iter_t	*it)
{

	Vector2	mouse_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
	Vector2	mouse_pos_tiled = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
	mouse_pos_tiled = Vector2Divide(mouse_pos, (Vector2){TILE_SZ, TILE_SZ});
	DrawText(TextFormat("%f,%f", mouse_pos_tiled.x, mouse_pos_tiled.y), mouse_pos.x, mouse_pos.y - 10, 5, PURPLE);
	DrawCircle(mouse_pos.x, mouse_pos.y, 2, BLUE);

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		ecs_entity_t	tile = ecs_new_id(it->world);
		Position pos = Vector2ToPos(mouse_pos_tiled);
		printf("pos: %d,%d\n", pos.x, pos.y);
		ecs_set(it->world, tile, Position, {pos.x, pos.y});
		ecs_set(it->world, tile, Tile, {49});
		ecs_add(it->world, tile, Collider);
	}
	if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
	{
		Position pos = Vector2ToPos(mouse_pos_tiled);
		ecs_entity_t	*tile = check_collision(pos, it->ctx, it->world);
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
		ecs_entity_t	*e = raycast_entity((Vector2) {pos.x, pos.y}, Vector2Normalize(Vector2Subtract(mouse_pos_tiled, pos)), 10, it->ctx, it->world);
		if (e)
			ecs_delete(it->world, *e);
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	/* if (IsKeyPressed(KEY_Q)) */
	{
		ecs_entity_t	player = ecs_lookup(it->world, "Player");
		const Position	* pos_p =ecs_get(it->world, player, Position);
		pos = PosToVector2(*pos_p);
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*arr = ecs_get(it->world, game_map, Arr2D);
	int	**map = *arr;
		pos = (Vector2) {pos.x + 0.5f, pos.y + 0.5f};
		target = raycast((Vector2) {pos.x, pos.y}, Vector2Normalize(Vector2Subtract(mouse_pos_tiled, pos)), 10, map);
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
