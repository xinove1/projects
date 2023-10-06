#ifndef MICRO_ROGUELIKE
# define MICRO_ROGUELIKE
# include <raylib.h>
# include <raymath.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define TILE_SIZE 8
# define TILEMAP_WIDTH (16 * TILE_SIZE)
# define TILEMAP_HEIGHT (10 * TILE_SIZE)
# define TILE_DEFAULT 17
# define PLAYER_SPRITE 4
# define ENEMY_SPRITE 6
# define RED_TRANSPARENT        CLITERAL(Color){ 230, 41, 55, 50 }     // Red

typedef enum Interactives {PLAYER = 1, ENEMY, WALL} Interactives;

typedef struct
{
	Vector2		size;
	int			**tiles;
	int			**interactives;// TODO better name
}GameMap;

typedef struct
{
	bool	selecting;
	bool	painting;
	int		tile;
	int		render_scale;
	Vector2	render_pos;
	Vector2	mouse_pos;
} TileSelector;

typedef struct
{
	int		health;
	Vector2	pos;
}Player;

typedef struct
{
	int		health;
	Vector2	pos;
	int		path_size;
	int		path_pos;
	Vector2	*path;
}Enemy;

typedef struct
{
	int		screen_width;
	int		screen_height;
	int		target_fps;
	char	*window_title;
	// which version of the assets
} Config;

typedef struct
{
	Texture2D		tilemap_texture;
	TileSelector	tile_selector;
	bool			paint_collisions;
	bool			draw_collisions;
	Camera2D		camera;
	GameMap			map;
	Player			player;
	bool			player_turn;
	List			*enemys;
	List			*test;
} Data;

extern Data		data;
extern Config	config;

void	update_game();
int		save_map(GameMap map, char *file_name);
int		load_map(GameMap *map, char *file_name);

int		get_array(int	**array, Vector2 pos);
void	set_array(int	**array, Vector2 pos, int new_value);
int		Vector2Compare(Vector2 vec1, Vector2 vec2);
void	move(int **arr, Vector2 *to_move, Vector2 new_pos, int value);

void	update_enemys();
void	move_enemys();
void	move_enemy(Enemy *enemy);
void	spawn_enemy(int health, Vector2 pos);

//Render
void	render_game();
void	render_game2d();
void	draw_tile(int tile, Vector2 pos);
void	draw_game_map(GameMap map);
void	draw_tile_selector();

void	pathfind_test(Enemy *enemy, Vector2 target);
// algos
List	*breadth_first_search(int **grid, Vector2 grid_size, Vector2 starting_pos);
List	*pathfind_breadth_first(int **grid, Vector2 grid_size, Vector2 starting_pos, Vector2 goal);
#endif // MICRO_ROGUELIKE
