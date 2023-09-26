#include "game.h"

static void	init_data();
static void	init_config();

Config	config = {0};
Data	data = {0};

int main(void)
{
	init_config();
	init_data();

    InitWindow(config.screen_width, config.screen_height, config.window_title);
	SetExitKey(KEY_NULL);
    SetTargetFPS(config.target_fps);

	data.tilemap_texture = LoadTexture("assets/Tilemap/colored_tilemap_packed.png");
    while (!WindowShouldClose())
    {
		update_game();
        BeginDrawing();
			ClearBackground(RAYWHITE);
		BeginMode2D(data.camera);
			render_game2d();
		EndMode2D();
			render_game();
        EndDrawing();
	}
    CloseWindow();
    return 0;
}

static void	init_config()
{
	config.screen_height = 1300;
	config.screen_width = 1000;
	config.target_fps = 60;
	config.window_title = "Micro rpg";
}

static void	init_data()
{
	data.background.size = (Vector2) {10, 10};
	data.background.map = calloc(data.background.size.y, sizeof(GameTile *));
	for (int i = 0; i < data.background.size.y; i++)
	{
		data.background.map[i] = calloc(data.background.size.x, sizeof(GameTile));
		for (int x = 0; x < data.background.size.x; x++)
			data.background.map[i][x].tile = 17; // TODO change to const or macro
	}

    data.camera = (Camera2D){0};
    data.camera.zoom = 2.0f;
	data.camera.target = (Vector2){data.background.size.x / 2.0f, data.background.size.y / 2.0f};
	data.camera.offset = (Vector2){config.screen_width / 2.0f, config.screen_height / 2.0f};

	data.tile_selector = (TileSelector){0};
	data.tile_selector.painting = true;
	data.tile_selector.tile = 15;
	data.tile_selector.render_scale = 4;
}
