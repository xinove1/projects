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
	config.screen_height = 720;
	config.screen_width = 1000;
	config.target_fps = 60;
	config.window_title = "Micro rpg";
}

static void	init_data()
{
	data.map.size = (Vector2) {25, 20};
	data.map.tiles = calloc(data.map.size.y, sizeof(int *));
	data.map.interactives = calloc(data.map.size.y, sizeof(int *));
	for (int i = 0; i < data.map.size.y; i++)
	{
		data.map.tiles[i] = calloc(data.map.size.x, sizeof(int));
		data.map.interactives[i] = calloc(data.map.size.x, sizeof(int));
		for (int x = 0; x < data.map.size.x; x++)
		{
			data.map.tiles[i][x] = TILE_DEFAULT; // TODO change to const or macro
			data.map.interactives[i][x] = 0;
		}
	}

    data.camera = (Camera2D){0};
    data.camera.zoom = 2.0f;
	data.camera.target = (Vector2){data.map.size.x / 2.0f, data.map.size.y / 2.0f};
	data.camera.offset = (Vector2){config.screen_width / 2.0f, config.screen_height / 2.0f};

	data.tile_selector = (TileSelector){0};
	data.tile_selector.painting = true;
	data.tile_selector.tile = 15;
	data.tile_selector.render_scale = 4;

	data.draw_collisions = true;

	data.player.pos = (Vector2){4,5};
	data.player.health = 4;
	set_array(data.map.interactives, data.player.pos, PLAYER);
	spawn_enemy(4, (Vector2) {10,10});
}
