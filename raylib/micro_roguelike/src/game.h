#ifndef MICRO_ROGUELIKE
# define MICRO_ROGUELIKE
# include <raylib.h>
# include <raymath.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_SIZE 8
# define TILEMAP_WIDTH (16 * TILE_SIZE)
# define TILEMAP_HEIGHT (10 * TILE_SIZE)

typedef struct GameTile
{
	int		tile;
	bool	blocking;
	void	*object;
} GameTile;

typedef struct GameMap
{
	GameTile	**map;
	Vector2		size;
}GameMap;

typedef struct TileSelector
{
	bool	selecting;
	bool	painting;
	int		tile;
	int		render_scale;
	Vector2	render_pos;
	Vector2	mouse_pos;
} TileSelector;

typedef struct Config
{
	int		screen_width;
	int		screen_height;
	int		target_fps;
	char	*window_title;
	// which version of the assets
} Config;

typedef struct Data
{
	Texture2D		tilemap_texture;
	Camera2D		camera;
	GameMap			background;
	TileSelector	tile_selector;
} Data;

extern Data		data;
extern Config	config;

void	update_game();

//Render
void	render_game();
void	render_game2d();
void	draw_tile(int tile, Vector2 pos);
void	draw_game_map(GameMap map);
void	render_tile_selector();

#endif // MICRO_ROGUELIKE
