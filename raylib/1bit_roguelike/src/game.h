#ifndef GAME_H_
#define GAME_H_
# include "includes.h"
# include "components.h"
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
void	render_colliders_map(ecs_iter_t	*it);
void	fill_map(ecs_world_t *world, ecs_query_t	*colliders, ecs_entity_t	game_map);
void	place_game_border(ecs_world_t *world);

// Loading levels from ldtk
void	load_level(ecs_world_t *world);
void	load_grid(ecs_world_t *world);

// Update
void	input_player(ecs_iter_t *it);
void	game_loop(ecs_iter_t	*it);
void	camera_follow_player(ecs_iter_t *it);
void	despawn(ecs_iter_t *it);
void	update_colliders_map(ecs_iter_t *it);
ecs_entity_t	*check_collision(Position target, ecs_world_t *it_world);
ecs_entity_t	*check_entitys(Position target, ecs_query_t *colliders_query, ecs_world_t *it_world);

// Actions
void	basic_enemy_state_machine(ecs_entity_t *enemy, ecs_world_t *ecs);
ecs_entity_t	*move(Vector2 dir, ecs_entity_t *e, ecs_world_t *ecs);
ecs_entity_t	*move_to_pos(Vector2 pos, ecs_entity_t *e, ecs_world_t *ecs);
void	attack(int damage, ecs_entity_t *target, ecs_world_t *ecs);

// Render
void	render_ui(ecs_iter_t *it);
void	render_tiles(ecs_iter_t *it);
void	render_health(ecs_iter_t *it);
void	flash_color(ecs_iter_t *it);
void	render_sight(ecs_iter_t *it);

// Erhm
void	pathfind(ecs_iter_t *it);
void	test_raycast(ecs_iter_t	*it);
void	tick_deathtimer(ecs_iter_t *it);

// Utils
void	print_arr2d(Arr2D arr);

#endif // GAME_H_
