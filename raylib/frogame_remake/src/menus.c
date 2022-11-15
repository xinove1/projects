#include "frogame.h"
#include <raylib.h>

void	menu_main(t_data *data)
{
	Texture menu_texture = LoadTexture("Assets/MENU_BASIC2.png");

	Rectangle play_b = {5, 28, 20, 10};
	Rectangle credit_b = {5, 41, 20, 10};

	while (!WindowShouldClose())
	{
		int mouse_x = GetMouseX() / data->win_scale;
		int mouse_y = GetMouseY() / data->win_scale;

		// Check if inside play button
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec((Vector2){mouse_x, mouse_y}, play_b))
		{
			data->current_screen = GAMEPLAY;
			break ;
		}
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec((Vector2){mouse_x, mouse_y}, credit_b))
		{
			data->current_screen = CREDITS;
			break ;
		}

		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode2D(data->camera);
			DrawTexture(menu_texture, 0, 0, WHITE);
			DrawFPS(10, 10);
		EndMode2D();
		EndDrawing();
	}
	UnloadTexture(menu_texture);
	//FIXME
	if (WindowShouldClose())
		exit(0);
}

void	credit_main(t_data *data)
{
	Texture credits_texture = LoadTexture("Assets/CREDITOS.png");

	Rectangle exit_b = {14, 72, 20, 10};

	while (!WindowShouldClose())
	{
		int mouse_x = GetMouseX() / data->win_scale;
		int mouse_y = GetMouseY() / data->win_scale;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec((Vector2){mouse_x, mouse_y}, exit_b))
		{
			data->current_screen = MENU;
			break ;
		}
		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode2D(data->camera);
			DrawTexture(credits_texture, 0, 0, WHITE);
			DrawFPS(10, 10);
		EndMode2D();
		EndDrawing();
	}
	UnloadTexture(credits_texture);
	//FIXME
	if (WindowShouldClose())
		exit(0);
}

void	death_main(t_data *data)
{
	Texture		death_texture1 = LoadTexture("Assets/YOU_DIED1.png");
	Texture		death_texture2 = LoadTexture("Assets/YOU_DIED2.png");

	Rectangle	play_again_b = {4, 72, 40, 9};
	bool		new_highscore = 0;

	while (!WindowShouldClose())
	{
		int mouse_x = GetMouseX() / data->win_scale;
		int mouse_y = GetMouseY() / data->win_scale;

		if (!new_highscore && data->score > data->highscore)
		{
			new_highscore = true;
			data->highscore = data->score;
		}
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec((Vector2){mouse_x, mouse_y}, play_again_b))
		{
			data->current_screen = MENU;
			break ;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			printf("mouse x, y: %d, %d\n", mouse_x, mouse_y);
		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode2D(data->camera);
			if (new_highscore)
				DrawTexture(death_texture2, 0, 0, WHITE);
			else
				DrawTexture(death_texture1, 0, 0, WHITE);
			DrawFPS(10, 10);
			DrawRectangleRec(play_again_b, BLUE);
		EndMode2D();
		EndDrawing();
	}
	//TODO SAVE HIGHSCORE
	if (new_highscore)
		printf("NEW HIGHSCORE\n");
	UnloadTexture(death_texture1);
	UnloadTexture(death_texture2);
	//FIXME
	if (WindowShouldClose())
		exit(0);
}