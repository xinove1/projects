#include "frogame.h"
#include <raylib.h>
#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

static void		player_animation(t_player *player, bool time_dark);
static void		bat_animation(t_bat *bat, bool time_dark);
static t_player	init_player();
static t_bat	init_bat();

void	gameplay_main(t_data *data)
{
	t_player	player = init_player();
	t_bat		bat = init_bat();

	data->player = &player;


    while (!WindowShouldClose())
    {
        // Update
        player_animation(&player, data->time_dark);
        bat_animation(&bat, data->time_dark);

		if (IsKeyPressed(KEY_SPACE))
		{
			if (data->time_dark)
				data->time_dark = 0;
			else
				data->time_dark = 1;
		}
		if (IsKeyPressed(KEY_A))
			player.dir.x = -1;
		else if (IsKeyPressed(KEY_D))
			player.dir.x = 1;

        // Draw
        BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(data->camera);
				DrawTextureRec(player.texture, player.frame, player.position, WHITE);
			if (bat.blocking) DrawTextureRec(bat.texture, bat.frame, bat.position, WHITE);
		EndMode2D();
        EndDrawing();
    }
	exit(0);
    // De-Initialization
    UnloadTexture(player.sheet[0]);
    UnloadTexture(player.sheet[1]);
	UnloadTexture(bat.texture);
	data->player = NULL;
}

static void	player_animation(t_player *player, bool time_dark)
{
    static int current_frame = 0;
    static int frames_counter = 0;
    static int frames_speed = 8; // Number of spritesheet frames shown by second
	frames_counter++;

	if (frames_counter >= (60 / frames_speed))
	{
		frames_counter = 0;
		current_frame++;
		if (current_frame > 7) current_frame = 0;

		if (time_dark)
			player->texture = player->sheet[1];
		else
			player->texture = player->sheet[0];
		// NOTE move to if and else statment for performance? + change if to check if time dark changend
		player->frame.width = (float)player->texture.width / 7;
		if (player->dir.x < 0 && player->frame.width > 0)
			player->frame.width = -player->frame.width;
		player->frame.height = (float)player->texture.height / 3;
		player->frame.x = (float)current_frame * (float)player->texture.width / 7;
	}

	// Control frames speed
	if (IsKeyPressed(KEY_RIGHT)) frames_speed++;
	else if (IsKeyPressed(KEY_LEFT)) frames_speed--;
	if (frames_speed > MAX_FRAME_SPEED) frames_speed = MAX_FRAME_SPEED;
	else if (frames_speed < MIN_FRAME_SPEED) frames_speed = MIN_FRAME_SPEED;
	//printf("frameSpeed: %d \n", frames_speed);
}

static void	bat_animation(t_bat *bat, bool time_dark)
{
    static int current_frame = 0;
    static int frames_counter = 0;
    static int frames_speed = 6; // Number of spritesheet frames shown by second
	frames_counter++;

	if (frames_counter >= (60 / frames_speed) && bat->blocking)
	{
		frames_counter = 0;

		// Death animation
		if (time_dark)
		{
			current_frame++;
			ft_printf("is dark\n");
			if (current_frame > 5)
			{
				bat->frame.y = 0;
				bat->frame.x = 0;
				current_frame = 0;
				bat->blocking = 0;
			}
			if (current_frame == 3)
			{
				bat->frame.y = 1 * (float)bat->texture.height / 2;
				bat->frame.x = 0;
			}
			else
				bat->frame.x = (float)current_frame * (float)bat->texture.width / 3;
		}
		// Iddle animation
		else
			bat->frame.x = 0;
	}
	// NOTE move to main function
	// Revive bat
	else if (frames_counter >= 60 * 5 && !time_dark)
		bat->blocking = 1;

	// Control frames speed
	if (IsKeyPressed(KEY_RIGHT)) frames_speed++;
	else if (IsKeyPressed(KEY_LEFT)) frames_speed--;
	if (frames_speed > MAX_FRAME_SPEED) frames_speed = MAX_FRAME_SPEED;
	else if (frames_speed < MIN_FRAME_SPEED) frames_speed = MIN_FRAME_SPEED;
	//printf("frameSpeed: %d \n", frames_speed);
}

static t_player	init_player()
{
	t_player player;
	player.position = (Vector2){20, 20};
	player.dir = (Vector2){-1, 0};
	player.blocking = 1;
	player.can_jump = 1;
	player.on_wall = 0;
	player.speed = 20;
	player.type = PLAYER;
	player.sheet[0] = LoadTexture("Assets/Sprites/Player/MOVIMENTOS_SAPO_ON.png");
	player.sheet[1] = LoadTexture("Assets/Sprites/Player/MOVIMENTOS_SAPO_OFF.png");
	player.frame = (Rectangle) {0, 0, 0, 0};
	return player;
}

static t_bat	init_bat()
{
	t_bat	bat;

	bat.type = ENEMYS;
	//bat.hitbox =   ;
	bat.blocking = 1;
	bat.texture = LoadTexture("Assets/Sprites/INIMIGO_SHEET.png");
	bat.frame = (Rectangle){0, 0, 0, 0};
	bat.position = (Vector2){20, 50};
	bat.speed = 1;
	bat.frame.width = (float)bat.texture.width / 3;
	bat.frame.height = (float)bat.texture.height / 2;
	return bat;
}
