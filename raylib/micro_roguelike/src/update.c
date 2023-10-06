#include "game.h"

static void	camera_update();
static void	tile_selector();
static void	move_player();
static void	paint_map();

void	update_game()
{
	if(IsKeyPressed(KEY_C))
	{
		if (data.tile_selector.painting == true)
		{
			data.tile_selector.painting = false;
			data.paint_collisions = true;
		}
		else
		{
			data.tile_selector.painting = true;
			data.paint_collisions = false;
		}
	}
	if (data.player_turn)
		move_player();
	else
		update_enemys();
	tile_selector();
	paint_map();
	camera_update();
}

static void	paint_map()
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), data.camera);
		Rectangle game_area = {0, 0, data.map.size.x * TILE_SIZE, data.map.size.y * TILE_SIZE};
		if (!CheckCollisionPointRec(mouse_world_pos, game_area))
			return ;
		Vector2	tile = {mouse_world_pos.x / TILE_SIZE, mouse_world_pos.y / TILE_SIZE};

		if (data.tile_selector.painting && !data.tile_selector.selecting)
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				set_array(data.map.tiles, tile, data.tile_selector.tile);
			else
				set_array(data.map.tiles, tile, TILE_DEFAULT);
		}
		else if (data.paint_collisions)
		{
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && get_array(data.map.interactives, tile) == WALL)
				set_array(data.map.interactives, tile, 0);
			else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && get_array(data.map.interactives, tile) == 0)
				set_array(data.map.interactives, tile, WALL);
		}
	}
}

static void	move_player()
{
	Vector2	new_pos = {0};

	if (IsKeyPressed(KEY_A))
		new_pos = (Vector2) {-1, 0};
	if (IsKeyPressed(KEY_D))
		new_pos = (Vector2) {1, 0};
	if (IsKeyPressed(KEY_W))
		new_pos = (Vector2) {0, -1};
	if (IsKeyPressed(KEY_S))
		new_pos = (Vector2) {0, 1};
	if (IsKeyPressed(KEY_Q))
	{
		data.player_turn = false;
		return ;
	}

	new_pos = Vector2Add(new_pos, data.player.pos);
	if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x >= data.map.size.x || new_pos.y >= data.map.size.y)
		return ;
	if (get_array(data.map.interactives, new_pos) == 0)
	{
		move(data.map.interactives, &data.player.pos, new_pos, PLAYER);
		data.player_turn = false;
	}
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
		Rectangle tilemap_rec = {selector->render_pos.x, selector->render_pos.y, data.tilemap_texture.width * selector->render_scale, data.tilemap_texture.height * selector->render_scale};
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(selector->mouse_pos, tilemap_rec))
		{
			Vector2 mouse_pos = Vector2Subtract(selector->mouse_pos, selector->render_pos);
			mouse_pos = Vector2Divide(mouse_pos, (Vector2) {TILE_SIZE * selector->render_scale, TILE_SIZE * selector->render_scale});
			mouse_pos = (Vector2) {(int) mouse_pos.x, (int) mouse_pos.y};
			data.tile_selector.tile = mouse_pos.x + (mouse_pos.y * (TILEMAP_WIDTH / TILE_SIZE));
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
