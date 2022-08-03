#include "frogame.h"

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");

	Image png = LoadImage("so_long_remake/resources/p_01.png");
	Texture2D p = LoadTextureFromImage(png);
	UnloadImage(png);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
			DrawTexture(p, 50, 50, WHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

	UnloadTexture(p);
    CloseWindow();

    return 0;
}
