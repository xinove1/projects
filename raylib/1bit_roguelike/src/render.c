#include "game.h"

void	render_ui(ecs_iter_t *it)
{
	Rectangle rrec = (Rectangle){10,100, 40,30};
	if (GuiButton(rrec, "teste"))
		printf("oaeuhaoenuh\n");

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
		rec.x = (tile[i] % (int) TILEMAP_SZ.x) * TILE_SZ;
		rec.y = (tile[i] / TILEMAP_SZ.y) * TILE_SZ;
		DrawTextureRec(data.tilemap, rec, (Vector2) {pos[i].x * TILE_SZ, pos[i].y * TILE_SZ}, WHITE);
	}


	//
	Vector2	mouse_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
	Vector2	mouse_pos_tiled = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
	mouse_pos_tiled = Vector2Divide(mouse_pos, (Vector2){TILE_SZ, TILE_SZ});

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		ecs_entity_t	tile = ecs_new_id(it->world);
		Position pos = Vector2ToPos(mouse_pos_tiled);
		printf("pos: %d,%d\n", pos.x, pos.y);
		ecs_set(it->world, tile, Position, {pos.x, pos.y});
		ecs_set(it->world, tile, Tile, {49});
		ecs_add(it->world, tile, Collider);
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		ecs_entity_t	player = ecs_lookup(it->world, "Player");
		const Position	*pos = ecs_get(it->world, player, Position);
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*arr = ecs_get(it->world, game_map, Arr2D);
	int	**map = *arr;
		Vector2 target = raycast(PosToVector2(*pos), Vector2Normalize(Vector2Subtract(mouse_pos_tiled, PosToVector2(*pos))), 10, map);
		if (Vector2Compare(target,  Vector2Zero()))
			DrawLine(pos->x * TILE_SZ, pos->y * TILE_SZ, mouse_pos.x, mouse_pos.y, GREEN);
		else
			DrawLine(pos->x * TILE_SZ, pos->y * TILE_SZ, target.x * TILE_SZ, target.y * TILE_SZ, GREEN);
	}
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
		rec.x = (tile[i] % (int) TILEMAP_SZ.x) * TILE_SZ;
		rec.y = (tile[i] / TILEMAP_SZ.y) * TILE_SZ;
		float	color_alpha = Remap(colors[i].timer, 0, colors[i].duration, 0, 1);
		DrawRectangle(pos[i].x * TILE_SZ, pos[i].y * TILE_SZ, rec.width, rec.height, ColorAlpha(colors[i].color, color_alpha));
	}
}

void	prepare_draw(ecs_iter_t	*it)
{
	(void) it;
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(10, 10);
}

void	prepare_draw2D(ecs_iter_t *it)
{
	(void) it;

	BeginMode2D(data.camera);
}

void	end_draw2D(ecs_iter_t *it)
{
	(void) it;

	EndMode2D();
}

void	end_draw(ecs_iter_t *it)
{
	(void) it;

	EndDrawing();
}
