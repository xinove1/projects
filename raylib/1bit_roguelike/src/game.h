#ifndef GAME_H_
#define GAME_H_
# include "../../../mylibc/libft.h"
# include "../flecs/flecs.h"
# include "components.h"
# include "../../../../raylib/src/raylib.h"
# include "../../../../raylib/src/raymath.h"
# include "raygui.h"
# if defined(PLATFORM_WEB)
#  include <emscripten/emscripten.h>
# endif

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
	Texture2D	tilemap;
	Camera2D	camera;
	ecs_world_t	*ecs;
	Vector2		map_bounds;
} Data;


extern Config	config;
extern Data		data;

# define TILEMAP_SZ  (Vector2) {49, 22}
# define TILE_SZ  16
# define ENERGY_THRESHOLD 10
# define COLLISION 1

void	init_ecs();

// Map
void	render_path(ecs_iter_t *it);
void	render_colliders_map(ecs_iter_t	*it);
void	fill_map(ecs_world_t *world, ecs_query_t	*colliders, ecs_entity_t	game_map);

// Update
void	input_player(ecs_iter_t *it);
void	game_loop(ecs_iter_t	*it);
void	camera_follow_player(ecs_iter_t *it);
void	move(ecs_iter_t *it);
void	attack(ecs_iter_t *it);
void	despawn(ecs_iter_t *it);
void	on_new_collider(ecs_iter_t *it);
ecs_entity_t	*check_collision(Position target, ecs_query_t *colliders_query, ecs_world_t *it_world);

// Render
void	render_ui(ecs_iter_t *it);
void	render_tiles(ecs_iter_t *it);
void	render_health(ecs_iter_t *it);
void	prepare_draw(ecs_iter_t	*it);
void	prepare_draw2D(ecs_iter_t *it);
void	end_draw2D(ecs_iter_t *it);
void	end_draw(ecs_iter_t *it);
void	flash_color(ecs_iter_t *it);

// Erhm
Vector2	raycast(Vector2 origin, Vector2 dir, int lenght, Arr2D map);
ecs_entity_t	*raycast_entity(Vector2 origin, Vector2 dir, int lenght, ecs_query_t *entitys, ecs_world_t *world);
void	pathfind(ecs_iter_t *it);
void	pathfind_a_star(Path *path, Vector2 start, Vector2 target, Arr2D map);
List	*pathfind_breadth_first(Arena *arena, Arena *scratch, Arr2D grid, Vector2 grid_size, Vector2 starting_pos, Vector2 goal);
void	test_raycast(ecs_iter_t	*it);
void	tick_deathtimer(ecs_iter_t *it);

// Utils
int		get_array(int	**array, Vector2 pos);
void	set_array(int	**array, Vector2 pos, int new_value);
void	print_arr2d(Arr2D arr);
int		Vector2Compare(Vector2 vec1, Vector2 vec2);// NOTE rename?
Position	Vector2ToPos(Vector2 v);
Vector2		PosToVector2(Position p);

#endif // GAME_H_
