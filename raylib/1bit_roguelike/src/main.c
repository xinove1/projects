#define RAYGUI_IMPLEMENTATION
#define RAYCAST_MODULE_IMPLEMENTATION
#include "game.h"
#define BASIC_COMPONENTS_MODULE_IMPLEMENTATION
#define PATHFIND_MODULE_IMPLEMENTATION
#include "modules/basic_components_module.h"
#include "modules/pathfind_module.h"

static void	init_config();
void	UpdateDrawFrame(void);

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
	data.camera.offset = (Vector2){config.screen_width / 2.0f, config.screen_height / 2.0f};

	// Raylib inici
	InitWindow(config.screen_width, config.screen_height, config.window_title);
	SetExitKey(KEY_NULL);
	data.tilemap = LoadTexture("assets/Tilesheet/colored-transparent_packed.png");
	SetTargetFPS(config.target_fps);

	//ECS_SYSTEM(data.ecs, render_tiles, OnDraw, Position, Tile);
	while (ecs_progress(data.ecs, GetFrameTime()) && !WindowShouldClose()) ;
	CloseWindow();
	ecs_fini(data.ecs);
	return 0;
}

// NOTE Web requirement if not compiling with async, remove?
void	UpdateDrawFrame(void)
{
	ecs_progress(data.ecs, GetFrameTime());
}

static void	init_config()
{
	config.screen_height = 720;
	config.screen_width = 1000;
	config.target_fps = 60;
	config.window_title = "1bit rpg";
}
