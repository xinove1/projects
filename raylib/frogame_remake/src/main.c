#include "frogame.h"

int main(void)
{
	// Inialize most structs and variables
	t_data		data = {0};
	t_screen	current_screen = MENU;
	bool		window_exit = false;

	// Load every texture needed


	// Load highscore from .data


	//

	// Window
	data.win_scale = 8.0f;
	data.win_width = 48 * data.win_scale;
	data.win_height = 84 * data.win_scale;

	// Camera
    data.camera.target = (Vector2){ 0 };
    data.camera.offset = (Vector2){ 0 };
    data.camera.rotation = 0.0f;
    data.camera.zoom = data.win_scale;

	// Raylib
    SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works
    InitWindow(data.win_width, data.win_height, "Frogame Remake");
	SetTargetFPS(60);

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
