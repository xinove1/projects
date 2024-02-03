#include "game.h"

//
//
char	*pieces[7] = {0};
Vector2	board_size = {12, 18};
char	*board = NULL;
int		made_lines[18] = {0}; // NOTE hard coded
bool	is_made_lines = false;

// Drawing related
Vector2	board_offset = {50};
int		tile_size = 16;
Color	piece_colors[9] = {BLUE, YELLOW, RED, GREEN, ORANGE, PINK, PURPLE, BLACK, DARKPURPLE};

int		rotate(Vector2 pos, int r);
int		check_piece_collision(int piece, Vector2 pos, int rotation);
void	draw_piece(int piece, Vector2 pos, int rotation);
void	draw_board();
int		check_line_made(Vector2 pos);
void	cleanup_made_lines();

int	main()
{
	pieces[0] = "..X."
				"..X."
				"..X."
				"..X.";

	pieces[1] = "...."
				".XX."
				".XX."
				"....";

	pieces[2] = "..X."
				".XX."
				".X.."
				"....";

	pieces[3] = ".X.."
				".XX."
				"..X."
				"....";

	pieces[4] = ".X.."
				".X.."
				".XX."
				"....";

	pieces[5] = "..X."
				"..X."
				".XX."
				"....";

	pieces[6] = "..X."
				"..XX"
				"..X."
				"....";

	board = malloc(board_size.x * board_size.y);
	for (int y = 0; y < board_size.y; y++)
		for (int x = 0; x < board_size.x; x++)
			board[y * (int)board_size.x + x] = (x == 0 || x == board_size.x - 1 || y == board_size.y -1) ? 8 : 0;

	Vector2	window_size = {600, 600};
	board_offset = (Vector2){window_size.x/2 - board_size.x/2, 100};

	InitWindow(window_size.x, window_size.y, "Tetris");
	SetTargetFPS(60);

	bool	game_over = false;
	bool	rotate_hold = false;

	Vector2	pos = {0};
	int		piece = 0;
	int		rotation = 0;


	bool	force_pieces_down = false;
	int		score = 0;
	int		speed = 20;
	int		speed_count = 0;
	int		piece_count = 0;
	float	frame_count = 0;
	while (!WindowShouldClose() && !game_over)
	{
		//WaitTime(0.50);

		//printf("fps: %d\n", GetFPS());

		// Timing
		if (frame_count < 5)
			frame_count++;
		else { // Game Logic
			frame_count = 0;

		speed_count++;
		if (speed_count == speed)
			force_pieces_down = true;

		// Logic
		if (IsKeyDown(KEY_A) && !check_piece_collision(piece, (Vector2){pos.x - 1, pos.y}, rotation))
			pos = (Vector2) {pos.x - 1, pos.y};
		if (IsKeyDown(KEY_D) && !check_piece_collision(piece, (Vector2){pos.x + 1, pos.y}, rotation))
			pos = (Vector2) {pos.x + 1, pos.y};
		if (IsKeyDown(KEY_S) && !check_piece_collision(piece, (Vector2){pos.x, pos.y + 1}, rotation))
			pos = (Vector2) {pos.x, pos.y + 1};
		if (IsKeyPressed(KEY_C))
		{
			piece += 1;
			if (piece == 7)
				piece = 0;
		}
		if (IsKeyDown(KEY_Z))
		{
			if (!rotate_hold && !check_piece_collision(piece, (Vector2){pos.x, pos.y}, rotation + 1))
			{
				rotation += 1;
				if (rotation == 4)
					rotation = 0;
			}
			rotate_hold = true;
		}
		else
			rotate_hold = false;

		if (force_pieces_down)
		{
			speed_count = 0;
			piece_count++;
			if (piece_count % 10 == 0) //NOTE hardcoded
				if (speed >= 10) speed--; //NOTE hardcoded

			if (!check_piece_collision(piece, (Vector2){pos.x, pos.y + 1}, rotation))
				pos.y += 1;
			else
			{

				for (int y = 0; y < 4; y++)
				{
					for (int x = 0; x < 4; x++)
					{
						Vector2	bpos = {pos.x + x, pos.y + y};
						if (pieces[piece][rotate((Vector2){x,y}, rotation)] == 'X')
							board[(int)(bpos.y * board_size.x + bpos.x)] = piece+1;
					}
				}

				int	lines_made_count = check_line_made(pos);
				score += 25;
				score += (1 << lines_made_count) * 100;

				pos.x = board_size.x/2;
				pos.y = 0;
				rotation = 0;
				piece = rand() % 7;

				game_over = check_piece_collision(piece, (Vector2){pos.x, pos.y}, rotation);
			}
			force_pieces_down = false;
		}
		if (is_made_lines)
		{
			printf("AAAAAAAAaa\n");
			WaitTime(0.1);
			cleanup_made_lines();
		}


		}
		// Drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_board();
		draw_piece(piece, pos, rotation);
		EndDrawing();
	}
	CloseWindow();
	free(board);
	return (0);
}

void	draw_board()
{
	for (int y = 0; y < board_size.y; y++)
	{
		for (int x = 0; x < board_size.x; x++)
		{
			Vector2	draw_pos = Vector2Scale((Vector2){x, y}, tile_size); // Add Position in the board + position inside the 4x4 of the piece
			draw_pos = Vector2Add(draw_pos, board_offset);

			int	piece = board[y * (int)board_size.x + x];
			if (piece != 0)
				DrawRectangle(draw_pos.x, draw_pos.y, tile_size, tile_size, piece_colors[piece - 1]);
		}
	}
}

void	draw_piece(int piece, Vector2 pos, int rotation)
{
	if (piece < 0 && piece > 6)
		return ;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pieces[piece][rotate((Vector2){x,y}, rotation)] != 'X')
				continue;
			Vector2	draw_pos = Vector2Add(pos,  (Vector2){x, y}); // Add Position in the board + position inside the 4x4 of the piece
			draw_pos = Vector2Scale(draw_pos, tile_size);
			draw_pos = Vector2Add(draw_pos, board_offset);
			DrawRectangle(draw_pos.x, draw_pos.y, tile_size, tile_size, piece_colors[piece]);
			//DrawRectangleLines(draw_pos.x, draw_pos.y, tile_size, tile_size, BLACK);
		}
	}
}

int	check_line_made(Vector2 pos)
{
	int	lines_made = 0;
	for (int y = 0; y < 4; y++)
	{
		bool	line_made = true;
		if (!(pos.y + y < board_size.y - 1))//NOTE
			continue;
		for (int x = 1; x < board_size.x - 1; x++)
			if (board[(int)((pos.y + y) * board_size.x + x)] == 0)
				line_made = false;
		if (line_made)
		{
			made_lines[(int)pos.y + y] = 1;
			is_made_lines = 1;
			for (int x = 1; x < board_size.x - 1; x++)
				board[(int)((pos.y + y) * board_size.x + x)] = 9;
		}
		lines_made += line_made;
	}
	return (lines_made);
}

void	cleanup_made_lines()
{
	for (int line = 0; line < board_size.y; line++)
	{
		printf("made_lines:%d\n", made_lines[line]);
		if (made_lines[line] != 1)
			continue;
		printf("soaneuhtsoaenuteoanuth\n");
		for (int x = 1; x < board_size.x - 1; x++)
		{
			printf("line:%d, x:%d\n", line, x);
			board[line * (int)board_size.x + x] = 0;
			for (int y = line; y > 0; y--)
				board[y * (int)board_size.x + x] = board[(y - 1) * (int)board_size.x + x];
		}
		made_lines[line] = -1;
	}
	is_made_lines = false;
}

int	check_piece_collision(int piece, Vector2 pos, int rotation)
{
	if (piece < 0 && piece > 6)
		return (1);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pieces[piece][rotate((Vector2){x,y}, rotation)] != 'X')
				continue;
			Vector2	check = Vector2Add(pos, (Vector2){x, y});
			if (!(check.x < 0 || check.x > board_size.x || check.y < 0 || check.y > board_size.y))
			{
				if (board[(int)(check.y * board_size.x + check.x)] != 0)
					return (1);
			}
		}
	}
	return (0);
}

int	rotate(Vector2 pos, int r)
{
	//r = r % 4;
	if (r == 0)
		return (pos.y * 4 + pos.x);
	if (r == 1)
		return (12 + pos.y - (pos.x * 4));
	if (r == 2)
		return (15 - (pos.y * 4) - pos.x);
	if (r == 3)
		return (3 - pos.y + (pos.x * 4));
	return (0);
}
