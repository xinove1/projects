#include "frogame.h"
#include <raylib.h>

int main(void)
{
	t_data	data = {0};
	data.current_screen = MENU;

	// Window
	data.win_scale = 8.0f;
	data.win_width = 48 * data.win_scale;
	data.win_height = 84 * data.win_scale;

	// Camera
    data.camera.target = (Vector2){ 0 };
    data.camera.offset = (Vector2){ 0 };
    data.camera.rotation = 0.0f;
    data.camera.zoom = data.win_scale;

    InitWindow(data.win_width, data.win_height, "raylib [core] example - basic window");
	SetTargetFPS(60);

    while (!WindowShouldClose())
    {
		switch (data.current_screen)
		{
			case MENU:
				menu_main(&data);
			break ;

			case CREDITS:
				credit_main(&data);
			break ;

			case GAMEPLAY:
				gameplay_main(&data);
			break ;

			case DEATH:
				death_main(&data);
			break ;
		}
    }

    CloseWindow();
    return 0;
}
