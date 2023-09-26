#include "game.h"

static void	camera_update();
static void	tile_selector();

void	update_game()
{
	tile_selector();
	if (data.tile_selector.painting && !data.tile_selector.selecting && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
		Rectangle game_area = {0, 0, data.background.size.x * TILE_SIZE, data.background.size.y * TILE_SIZE};
		if (!CheckCollisionPointRec(mouse_world_pos, game_area))
			return ;
		Vector2	tile = {mouse_world_pos.x / TILE_SIZE, mouse_world_pos.y / TILE_SIZE};
		data.background.map[(int) tile.y][(int) tile.x].tile = data.tile_selector.tile;
	}
	camera_update();
}

static void	tile_selector()
{
	TileSelector	*selector = &data.tile_selector;

	if (IsKeyPressed(KEY_E))
	{
		if (selector->selecting == false)
			selector->selecting = true;
		else
			selector->selecting = false;
		selector->render_pos = GetMousePosition();
	}
	if (selector->selecting)
	{
		selector->mouse_pos = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mouse_pos = Vector2Subtract(selector->mouse_pos, selector->render_pos);
			mouse_pos = Vector2Divide(mouse_pos, (Vector2) {TILE_SIZE * selector->render_scale, TILE_SIZE * selector->render_scale});
			mouse_pos = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
			printf("mouse_pos: %f,%f\n", mouse_pos.x, mouse_pos.y);
			data.tile_selector.tile = mouse_pos.x + (mouse_pos.y * (TILEMAP_WIDTH / TILE_SIZE));
			printf("tile %d\n", data.tile_selector.tile);
		}
	}
}

static void	camera_update()
{

	if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
	{
		Vector2 delta = GetMouseDelta();
		delta = Vector2Scale(delta, -1.0f/data.camera.zoom);
		data.camera.target = Vector2Add(data.camera.target, delta);
	}

	float wheel = GetMouseWheelMove();
	if (wheel != 0)
	{
		Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
		data.camera.offset = GetMousePosition();
		data.camera.target = mouse_world_pos;
		const float zoom_increment = 0.525f;
		data.camera.zoom += (wheel * zoom_increment);
		if (data.camera.zoom < zoom_increment)
			data.camera.zoom = zoom_increment;
		/* printf("offset: %f,%f\n", data.camera.offset.x, data.camera.offset.y); */
		/* printf("target: %f,%f\n", data.camera.target.x, data.camera.target.y); */
	}
}
