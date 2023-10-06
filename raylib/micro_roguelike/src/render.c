#include "game.h"

void	draw_interactives(GameMap map);
void	draw_debug_stuff2d();
void	draw_debug_stuff();

void	render_game()
{
	if (data.tile_selector.selecting)
		draw_tile_selector();
	if (data.paint_collisions)
		DrawText("Panting Mode: collisions", 0, 0, 20, BLUE);
	else if (data.tile_selector.painting)
		DrawText("Panting Mode: tiles", 0, 0 , 20, BLUE);
	else
		DrawText("Panting Mode: None", 0, 0 , 20, BLUE);

	draw_debug_stuff();
}

void	render_game2d()
{
	draw_game_map(data.map);
	draw_interactives(data.map);
	draw_debug_stuff2d();
}

void	draw_debug_stuff2d()
{
	// List of Vector2 from pathfinding
	List	*list = data.test;
	while (list)
	{
		Vector2	pos = *((Vector2 *) list->content);
		DrawRectangle(pos.x * TILE_SIZE, pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED_TRANSPARENT);
		/* printf("pos: %f, %f\n", pos.x, pos.y); */
		list = list->next;
	}

	//
}
void	draw_debug_stuff()
{
	int	scale = data.tile_selector.render_scale;
	//Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
	Vector2 mouse_world_pos = GetMousePosition();
	Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);;
	mouse_pos = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
	mouse_pos = Vector2Divide(mouse_pos, (Vector2){TILE_SIZE, TILE_SIZE});
	DrawText(TextFormat("%d,%d", (int) mouse_pos.x ,(int)mouse_pos.y), mouse_world_pos.x+ 20, mouse_world_pos.y, 25, BLUE);
}

void	draw_tile_selector()
{
	int	scale = data.tile_selector.render_scale;
	data.tile_selector.render_pos =(Vector2) {config.screen_width/3, config.screen_height/2};
	Vector2	pos = data.tile_selector.render_pos;
	Vector2	mouse_pos =  data.tile_selector.mouse_pos;
	DrawTextureEx(data.tilemap_texture, pos, 0, scale, WHITE);

	Rectangle tilemap_rec = {pos.x, pos.y, data.tilemap_texture.width * scale, data.tilemap_texture.height * scale};
	if (CheckCollisionPointRec(mouse_pos, tilemap_rec))
	{
		//printf("mouse_pos: %f,%f\n", mouse_pos.x, mouse_pos.y);
		mouse_pos = Vector2Subtract(mouse_pos, pos);
		mouse_pos = Vector2Divide(mouse_pos, (Vector2) {TILE_SIZE * scale, TILE_SIZE * scale});
		mouse_pos = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
		mouse_pos = Vector2Multiply(mouse_pos, (Vector2){TILE_SIZE * scale, TILE_SIZE * scale});
		mouse_pos = Vector2Add(mouse_pos, pos);
		DrawRectangleLines(mouse_pos.x, mouse_pos.y, TILE_SIZE * scale, TILE_SIZE * scale, RED);
	}
}

void	draw_interactives(GameMap map)
{
	for (int y = 0; y < map.size.y; y++)
	{
		for (int x = 0; x < map.size.x; x++)
		{
			if (map.interactives[y][x] == PLAYER)
				draw_tile(PLAYER_SPRITE, (Vector2) {x * TILE_SIZE, y * TILE_SIZE});
			else if (map.interactives[y][x] == ENEMY)
				draw_tile(ENEMY_SPRITE, (Vector2) {x * TILE_SIZE, y * TILE_SIZE});
			if (data.draw_collisions && map.interactives[y][x] != 0)
				DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED_TRANSPARENT);
		}
	}
}

void	draw_game_map(GameMap map)
{
	DrawText("Game Map bounds", 0, -10, 8, RED);
	DrawRectangleLines(-1, -1, map.size.x * TILE_SIZE + 2, map.size.y * TILE_SIZE + 2, BLACK);
	for (int y = 0; y < map.size.y; y++)
	{
		for (int x = 0; x < map.size.x; x++)
			draw_tile((map.tiles[y][x]), (Vector2) {x * TILE_SIZE, y * TILE_SIZE});
	}
}

void	draw_tile(int tile, Vector2 pos)
{
	Rectangle	rec;

	// NOTE take out later?
	if (tile >= 160 || tile < 0)
	{
		fprintf(stderr, "ERROR: draw_tile(): invalid tile\n");
		return ;
	}
	rec.height = TILE_SIZE;
	rec.width  = TILE_SIZE;
	rec.x = (tile % TILEMAP_WIDTH) * TILE_SIZE;
	rec.y = (tile / 16) * TILE_SIZE;
	DrawTextureRec(data.tilemap_texture, rec, pos, WHITE);
}
