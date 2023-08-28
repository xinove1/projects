#ifndef SO_LONG_H
#define SO_LONG_H
# include "raylib.h"
# include <stdio.h>
# include <fcntl.h>
# include "./libft/libft.h"
# define TILE_SIZE 16

typedef struct s_Vector2
{
	int		x;
	int		y;
}			t_Vector2;

typedef struct s_game
{
	char		**map;
	t_Vector2	map_size;
	int			collectables;
	int			collected;
	int			players;
	t_Vector2	*players_p;
	int			moves;
	Texture2D	tiles[7];
	int			player_state;
	int			map_changed;
}				t_game;

void		clean_map(char **map);
void		clean(t_game *game, void *ptr);
void		parse_map(t_game *game, char *map_path);
t_Vector2	get_map_size(char *path, t_game *game);
void		get_map(t_game *game, char *path);
void		check_walls(t_game *game);
void		parse_players_position(t_game *game);
void		move(t_game *game, t_Vector2 dir);
void		print_map(t_game *game);
t_Vector2	add_vec2(t_Vector2 p1, t_Vector2 p2);
void		parser_error_handler(int error, t_game *game, void *ptr);
void		change_map(t_game *game, t_Vector2 target, char c);
void		change_player_pos(t_game *game, int i, t_Vector2 dir);
int			draw(t_game *game);
int			handle_keys(t_game *game);
void		init_images(t_game	*game);
int			exit_game(t_game *game);
void		parse_inner_map(t_game *game);
void		draw_tile(t_game *g, int x, int y);
void		init_mlx(t_game	*game);
void		init_values(t_game *game);
void		print_credits(void);

#endif // SO_LONG_H_
