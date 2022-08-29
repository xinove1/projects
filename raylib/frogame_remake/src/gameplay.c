#include "frogame.h"
#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

static void	player_animation(t_data *data, Texture2D *dest_texture, Rectangle *frame);
static void	init_player(t_data *data);

void	gameplay_main(t_data *data)
{
	Texture2D	player_texture;
	Rectangle	player_frame = {0, 0, 0, 0};

	init_player(data);

    while (!WindowShouldClose())
    {
        // Update
        player_animation(data, &player_texture, &player_frame);
		if (IsKeyPressed(KEY_SPACE))
			data->time_dark = 1;

        // Draw
        BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(data->camera);
            /* DrawTexture(scarfy, 15, 40, WHITE); */
            /* DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME); */
            /* DrawRectangleLines(15 + (int)frameRec.x, 40 + (int)frameRec.y, (int)frameRec.width, (int)frameRec.height, RED); */
			DrawTextureRec(player_texture, player_frame, data->player->position, WHITE);
		EndMode2D();
        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(data->player->texture[0]);
    UnloadTexture(data->player->texture[1]);
	free(data->player);
}

static void	player_animation(t_data *data, Texture2D *dest_texture, Rectangle *frame)
{
    static int current_frame = 0;
    static int frames_counter = 0;
    static int frames_speed = 8;            // Number of spritesheet frames shown by second
	frames_counter++;

	if (frames_counter >= (60 / frames_speed))
	{
		frames_counter = 0;
		current_frame++;
		if (current_frame > 7) current_frame = 0;

		if (data->time_dark)
			*dest_texture = data->player->texture[1];
		else
			*dest_texture = data->player->texture[0];
		// NOTE move to if and else statment for performance? + change if to check if time dark changend
		frame->width = (float)dest_texture->width / 7;
		frame->height = (float)dest_texture->height / 3;
		frame->x = (float)current_frame * (float)dest_texture->width / 7;
	}

	// Control frames speed
	if (IsKeyPressed(KEY_RIGHT)) frames_speed++;
	else if (IsKeyPressed(KEY_LEFT)) frames_speed--;
	if (frames_speed > MAX_FRAME_SPEED) frames_speed = MAX_FRAME_SPEED;
	else if (frames_speed < MIN_FRAME_SPEED) frames_speed = MIN_FRAME_SPEED;
	printf("frameSpeed: %d \n", frames_speed);
}

static void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	t_player *player = data->player;
	player->position = (Vector2){20, 20};
	player->blocking = 1;
	player->can_jump = 1;
	player->on_wall = 0;
	player->speed = 20;
	player->type = PLAYER;
	player->texture[0] = LoadTexture("Assets/Sprites/Player/MOVIMENTOS_SAPO_ON.png");
	player->texture[1] = LoadTexture("Assets/Sprites/Player/MOVIMENTOS_SAPO_OFF.png");
}
