#include "game.h"

void	render_ui(ecs_iter_t *it)
{
	Rectangle rrec = (Rectangle){10,100, 40,30};
	if (GuiButton(rrec, "teste"))
		printf("oaeuhaoenuh\n");
}

void	render_sight(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	LineOfSight	*sight = ecs_field(it, LineOfSight, 2);

	for (int i = 0; i < it->count; i++)
	{
		Vector2	origin = PosToVector2(pos[i]);
		origin = Vector2Add(origin, (Vector2){0.5, 0.5});
		int		lenght = sight[i];
		Vector2	dir = {0, 0};
		for (int angle = 0; angle < 360; angle += 10)
		{
			dir = (Vector2) {cos(DEG2RAD * angle), sin(DEG2RAD * angle)};
			Vector2 pos = Vector2Add(Vector2Scale(origin, TILE_SZ), Vector2Scale(dir, lenght * TILE_SZ));
			ecs_entity_t *e = raycast_entity(origin, dir, lenght, it->world);
			if (e && ecs_has_id(it->world, *e, ecs_id(Player)))
				DrawLine(origin.x * TILE_SZ, origin.y * TILE_SZ, pos.x, pos.y, RED);
			else
				DrawLine(origin.x * TILE_SZ, origin.y * TILE_SZ, pos.x, pos.y, BLUE);
		}
	}
}

void	render_tiles(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Tile		*tile = ecs_field(it, Tile, 2);
	Rectangle	rec;
	rec.height = TILE_SZ;
	rec.width  = TILE_SZ;

	for (int i = 0; i < it->count; i++)
	{
		rec.x = tile[i].x * TILE_SZ;
		rec.y = tile[i].y * TILE_SZ;
		DrawTextureRec(data.tilemap, rec, (Vector2) {pos[i].x * TILE_SZ, pos[i].y * TILE_SZ}, WHITE);
	}

	/* Vector2 origin = {20,10}; */
	/* int	lenght = 10; */
	/* Vector2	dir = {0, 0}; */
	/* int	angle = 0; */
	/* for (angle = 0; angle < 360; angle += 9) */
	/* { */
	/* 	dir = (Vector2) {cos(DEG2RAD * angle), sin(DEG2RAD * angle)}; */
	/* 	Vector2 pos = Vector2Add(Vector2Scale(origin, TILE_SZ), Vector2Scale(dir, lenght * TILE_SZ)); */
	/* 	ecs_entity_t	*e = raycast_entity(origin, dir, lenght, it->world); */
	/* 	if (e) */
	/* 		DrawLine(origin.x * TILE_SZ, origin.y * TILE_SZ, pos.x, pos.y, RED); */
	/* 	else */
	/* 		DrawLine(origin.x * TILE_SZ, origin.y * TILE_SZ, pos.x, pos.y, BLUE); */
	/* } */
}


void	render_health(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Health		*health = ecs_field(it, Health, 2);

	for (int i = 0; i < it->count; i++)
	{
		Position	r_pos = {pos[i].x * TILE_SZ + 1, pos[i].y * TILE_SZ - 9};
		DrawText(TextFormat("%d", health[i]), r_pos.x, r_pos.y, 3, RED);
	}
}

void	flash_color(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Tile		*tile = ecs_field(it, Tile, 2);
	FlashColor	*colors = ecs_field(it, FlashColor, 3);// TODO better name
	Rectangle	rec;
	rec.height = TILE_SZ;
	rec.width  = TILE_SZ;

	for (int i = 0; i < it->count; i++)
	{
		colors[i].timer += it->delta_time;
		if (colors[i].timer >= colors[i].duration)
			ecs_remove(it->world, it->entities[i], FlashColor);
		rec.x = tile[i].x * TILE_SZ;
		rec.y = tile[i].y * TILE_SZ;
		float	color_alpha = Remap(colors[i].timer, 0, colors[i].duration, 0, 1);
		DrawRectangle(pos[i].x * TILE_SZ, pos[i].y * TILE_SZ, rec.width, rec.height, ColorAlpha(colors[i].color, color_alpha));
	}
}

void	render_colliders_map(ecs_iter_t	*it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*map = ecs_get(it->world, game_map, Arr2D);
	if (map->arr == NULL)
	{
		printf("Tryng to render a empty map \n");
		return ;
	}
	for (int y = 0; y < map->size.y; y++)
	{
		for (int x = 0; x < map->size.x; x++)
		{
			if (map->arr[y][x] == 0)
				continue;
			Position	d_pos = (Position) {x * TILE_SZ, y * TILE_SZ};
			DrawRectangle(d_pos.x, d_pos.y, TILE_SZ, TILE_SZ, ColorAlpha(RED, 0.3));
		}
	}
}
