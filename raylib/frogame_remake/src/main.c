#include "frogame.h"

static void	init_data(t_data *data);
static t_textures	load_textures();

int main(void)
{
	// Inialize most structs and variables
	t_data		data = {0};
	t_screen	current_screen = MENU;
	bool		window_exit = false;

	init_data(&data);
	// Load highscore from .data

	// Raylib
    SetExitKey(KEY_NULL); // Disable KEY_ESCAPE to close window, X-button still works
    InitWindow(data.win_width, data.win_height, "Frogame Remake");
	SetTargetFPS(60);

	data.textures = load_textures();

	t_map map = parse_map("test");
	for (int i = 0; i < map.sz.y; i++)
	{
		for (int j = 0; j < map.sz.x; j++)
			ft_printf("%c", map.map[i][j]);
		ft_printf("\n");
	}

    while (!window_exit)
    {
		switch (current_screen)
		{
			case MENU:
				current_screen = menu_main(&data);
			break ;

			case CREDITS:
				current_screen = credit_main(&data);
			break ;

			case GAMEPLAY:
				current_screen = gameplay_main(&data);
			break ;

			case DEATH:
				current_screen = death_main(&data);
			break ;

			case EXIT_GAME:
				//TODO SAVE HIGHSCORE
				window_exit = true;
			break ;
		}
    }
	//TODO Memory cleanup before exit
    CloseWindow();
}

static t_textures	load_textures()
{
	t_textures	textures = {0};
	textures.screens[0] = LoadTexture("Assets/menu_screen.png");
	textures.screens[1] = LoadTexture("Assets/credits_screen.png");
	textures.screens[2] = LoadTexture("Assets/death_screen1.png");
	textures.screens[3] = LoadTexture("Assets/death_screen2.png");

	textures.bat_sheet = LoadTexture("Assets/Sprites/bat_sheet.png");
	textures.block 	= LoadTexture("Assets/Sprites/full_block_3x3.png");
	textures.spikes 	= LoadTexture("Assets/Sprites/spike.png");

	textures.ligth_switch[0] = LoadTexture("Assets/Sprites/lightswitch_off.png");
	textures.ligth_switch[1] = LoadTexture("Assets/Sprites/lightswitch_on.png");
	textures.player_sheet[0] = LoadTexture("Assets/Sprites/frog_sheet_on.png");
	textures.player_sheet[1] = LoadTexture("Assets/Sprites/frog_sheet_off.png");

	textures.lights_out[0] = LoadTexture("Assets/Sprites/blackground/lights_off1.png");
	textures.lights_out[1] = LoadTexture("Assets/Sprites/blackground/lights_off2.png");
	textures.lights_out[2] = LoadTexture("Assets/Sprites/blackground/lights_off3.png");
	textures.lights_out[3] = LoadTexture("Assets/Sprites/blackground/lights_off4.png");

	textures.death_anim[0] = LoadTexture("Assets/Sprites/death_animation/death0.png");
	textures.death_anim[1] = LoadTexture("Assets/Sprites/death_animation/death1.png");
	textures.death_anim[2] = LoadTexture("Assets/Sprites/death_animation/death2.png");
	textures.death_anim[3] = LoadTexture("Assets/Sprites/death_animation/death3.png");
	textures.death_anim[4] = LoadTexture("Assets/Sprites/death_animation/death4.png");
	textures.death_anim[5] = LoadTexture("Assets/Sprites/death_animation/death5.png");
	textures.death_anim[6] = LoadTexture("Assets/Sprites/death_animation/death6.png");
	textures.death_anim[7] = LoadTexture("Assets/Sprites/death_animation/death7.png");
	return (textures);
}

static void	init_data(t_data *data)
{
	// Window
	data->win_scale = 8.0f;
	data->win_width = 48 * data->win_scale;
	data->win_height = 84 * data->win_scale;

	// Camera
    data->camera.target = (Vector2){ 0 };
    data->camera.offset = (Vector2){ 0 };
    data->camera.rotation = 0.0f;
    data->camera.zoom = data->win_scale;
}
