#include "game.h"

void	render_game()
{
	if (data.tile_selector.selecting)
		render_tile_selector();
}

void	render_game2d()
{
	draw_game_map(data.background);
}

void	render_tile_selector()
{
	int	scale = data.tile_selector.render_scale;
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

void	draw_game_map(GameMap map)
{
	DrawText("Game Map bounds", 0, -10, 8, RED);
	DrawRectangleLines(-1, -1, map.size.x * TILE_SIZE + 2, map.size.y * TILE_SIZE + 2, BLACK);
	for (int y = 0; y < map.size.y; y++)
	{
		for (int x = 0; x < map.size.x; x++)
			draw_tile((map.map[y][x]).tile, (Vector2) {x * TILE_SIZE, y * TILE_SIZE});
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
