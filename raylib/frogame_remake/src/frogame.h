#ifndef FROGAME_H
# define FROGAME_H
# include "raylib.h"
# include "stdio.h"
# include "fcntl.h"
# include "./../../../libft/libft.h"
# define G 400
# define JUMP_SPEED 350.0f
# define SPEED 200.0f

typedef enum e_game_screen {MENU, CREDITS, GAMEPLAY, DEATH, EXIT_GAME} t_screen;
typedef enum e_entities_types {WORLD, INTERACTABLE, PLAYER, ENEMYS} t_entities_type;

typedef struct s_player
{
	t_entities_type	type;
    Rectangle	hitbox;
    int			blocking;
	Texture2D	sheet[2];
	Texture2D	texture;
	Rectangle	frame;
    Vector2		position;
	Vector2		dir;
    float		speed;
	bool		on_wall;
    bool		can_jump;
} t_player;

typedef struct s_bat
{
	t_entities_type	type;
    Rectangle	hitbox;
    int			blocking;
	Texture2D	texture;
	Rectangle	frame;
    Vector2		position;
    float		speed;
} t_bat;

typedef struct s_entities {
	t_entities_type	type;
    Rectangle	hitbox;
    int			blocking;
} t_entities;

typedef struct s_data
{
	t_player	player;
	t_entities	*ent_lst;
	bool		is_dark;
	Camera2D	camera;
	int			time_dark;
	int			score;
	int			highscore;
	int			win_height;
	int			win_width;
	float		win_scale;
} t_data;

typedef struct s_block {
	t_entities_type	type;
    Rectangle	hitbox;
    int			blocking;
	Texture2D	*texture;
} t_block;

typedef struct s_map
{
	Vector2	sz;
	char	**map;
} t_map;

int	menu_main(t_data *data);
int	credit_main(t_data *data);
int	death_main(t_data *data);
int	gameplay_main(t_data *data);

t_map 	parse_map(char *file);
#endif // FROGAME_H
