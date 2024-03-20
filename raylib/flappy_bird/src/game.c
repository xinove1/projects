#include "game.h"

typedef struct
{
	Vector2	pos;
	Rectangle	collision_box;
	Vector2	velocity;
}Player_t;

Vector2	window_sz = {600, 600};
Player_t	player = {{10,10}, {0,0, 15, 10}, 0};

void	draw_test_recs();

int	main(void)
{
	InitWindow(window_sz.x, window_sz.y, "Flappy bird clone");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Vector2	dir = {0, 0};
		if (IsKeyPressed(KEY_A))
			dir.x += -1;
		if (IsKeyPressed(KEY_D))
			dir.x += 1;
		if (IsKeyPressed(KEY_W))
			dir.y += -1;
		if (IsKeyPressed(KEY_S))
			dir.y += 1;
		//player.velocity = Vector2Scale(dir, 20);
		if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
		{
			Vector2	mouse_dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.pos));
			player.velocity = Vector2Add(Vector2Scale(mouse_dir, 20), player.velocity);
		}
		/* player.velocity.x += dir.x; */
		/* player.velocity.y += dir.y; */

		BeginDrawing();
		ClearBackground(BLUE);
		draw_test_recs();
		EndDrawing();
	}
}

void	draw_test_recs()
{
	Vector2 mouse_pos = GetMousePosition();

	Rectangle a = {100, 100, 100, 100};
	Vector2	ray_point = {20, 20};
	Vector2	ray_dir = Vector2Subtract(mouse_pos, ray_point);

	Vector2	contact_point, contact_normal;
	float	time;
	if (CheckCollisionDynamicRectRect(player.pos, player.collision_box, player.velocity, a, &contact_point, &contact_normal, &time, GetFrameTime()) && time < 1)
	{
		Vector2	vel = {fabsf(player.velocity.x), fabsf(player.velocity.y)};
		player.velocity = Vector2Add(player.velocity, Vector2Multiply(contact_normal, Vector2Scale(vel, 1 - time)));
		DrawCircleV(contact_point, 4, RED);
	}

	player.pos = Vector2Add(Vector2Scale(player.velocity, GetFrameTime()), player.pos);

	DrawLineV(ray_point, mouse_pos, GREEN);
	if (CheckCollisionRayRec(ray_point, ray_dir, a, &contact_point, &contact_normal, &time) && time < 1)
	{
		DrawRectangleRec(a, YELLOW);
		DrawCircleV(contact_point, 4, RED);
	}
	else
	{
		DrawRectangleRec(a, RED);
	}
	DrawRectangle(player.pos.x,player.pos.y, player.collision_box.width, player.collision_box.height, PURPLE);
}
