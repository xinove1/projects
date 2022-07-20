#include "so_long.h"

int	main(int argc, const char *argv[])
{
	t_game	game;

	init_values(&game);
	if (argc < 2)
		parser_error_handler(6, &game, NULL);
	else if (argc > 2)
		parser_error_handler(7, &game, NULL);
	parse_map(&game, (char *)argv[1]);

    InitWindow(game.map_size.x * TILE_SIZE, game.map_size.y * TILE_SIZE, "raylib [core] example - basic window");
	init_images(&game);
    while (!WindowShouldClose())
    {
		handle_keys(&game);
        BeginDrawing();
			if (game.map_changed)
				draw(&game);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int	draw(t_game *g)
{
	int		y;
	int		x;
	char	*moves;

	y = 0;
	while (y < g->map_size.y)
	{
		x = 0;
		while (x < g->map_size.x)
		{
			draw_tile(g, x, y);
			x++;
		}
		y++;
	}
	moves = ft_itoa(g->moves);
	//mlx_string_put(g->mlx_ptr, g->win, 3, 11, 255, moves);
	free(moves);
	g->map_changed = 0;
	return (0);
}

void	draw_tile(t_game *g, int i, int j)
{
	int	x;
	int	y;

	x = TILE_SIZE * i;
	y = TILE_SIZE * j;
	switch (g->map[j][i])
	{
		case '0':
			DrawTexture(g->tiles[3], x, y, WHITE);
		break;

		case '1':
			DrawTexture(g->tiles[4], x, y, WHITE);
		break;

		case 'P':
			DrawTexture(g->tiles[3], x, y, WHITE);
			if (g->player_state < 0)
				DrawTexture(g->tiles[0], x, y, WHITE);
			else
				DrawTexture(g->tiles[1], x, y, WHITE);
		break;

		case 'E':
			DrawTexture(g->tiles[5], x, y, WHITE);
		break;

		case 'C':
			DrawTexture(g->tiles[2], x, y, WHITE);
		break;
	}
}

void	init_images(t_game	*g)
{
	Image 	tmp;
	int		i;
	char	*files[6] = {"resources/p_01.png", "resources/p_02.png", "resources/collect.png",
						"resources/tile.png", "resources/wall.png", "resources/exit.png"};

	i = 0;
	while (i < 6)
	{
		tmp = LoadImage(files[i]);
		printf("loading image %s\n", files[i]);
		g->tiles[i] = LoadTextureFromImage(tmp);
		UnloadImage(tmp);
		i++;
	}
}
