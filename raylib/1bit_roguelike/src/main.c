#define RAYGUI_IMPLEMENTATION
#include "game.h"

static void	init_config();

Config	config = {0};
Data		data = {0};

int main(void)
{
	data.map_bounds.x = 30;
	data.map_bounds.y = 20;
	init_config();
	init_ecs();


	data.camera = (Camera2D){0};
	data.camera.zoom = 2.0f;
	//data.camera.target = (Vector2){data.map.size.x / 2.0f, data.map.size.y / 2.0f};
	data.camera.offset = (Vector2){config.screen_width / 2.0f, config.screen_height / 2.0f};

	// Raylib inici
	InitWindow(config.screen_width, config.screen_height, config.window_title);
	SetExitKey(KEY_NULL);
	SetTargetFPS(config.target_fps);

	//ECS_SYSTEM(data.ecs, render_tiles, OnDraw, Position, Tile);
	data.tilemap = LoadTexture("assets/Tilesheet/colored-transparent_packed.png");
	while (ecs_progress(data.ecs, GetFrameTime()) && !WindowShouldClose()) ;
	CloseWindow();
	// De-init
  return 0;
}

static void	init_config()
{
	config.screen_height = 720;
	config.screen_width = 1000;
	config.target_fps = 60;
	config.window_title = "1bit rpg";
}
