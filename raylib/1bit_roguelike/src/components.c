#include "game.h"

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Tile);
ECS_COMPONENT_DECLARE(Health);
ECS_COMPONENT_DECLARE(Dir);
ECS_COMPONENT_DECLARE(FlashColor);
ECS_COMPONENT_DECLARE(Attack);
ECS_COMPONENT_DECLARE(Arr2D);
ECS_COMPONENT_DECLARE(Path);

ECS_TAG_DECLARE(Despawn);
ECS_TAG_DECLARE(Player);
ECS_TAG_DECLARE(Enemy);
ECS_TAG_DECLARE(Collider);
ECS_TAG_DECLARE(Despawn);
ECS_TAG_DECLARE(TargetFollow);

ECS_DECLARE(PreUpdate);
ECS_DECLARE(OnUpdate);
ECS_DECLARE(PostUpdate);
ECS_DECLARE(PreDraw);
ECS_DECLARE(PreDraw2D);
ECS_DECLARE(OnDraw2D);
ECS_DECLARE(PostDraw2D);
ECS_DECLARE(OnDraw);
ECS_DECLARE(PostDraw);

static void	 setup_phases(ecs_world_t *ecs);
static void	 setup_tags(ecs_world_t *ecs);
static void	 setup_components(ecs_world_t *ecs);

void	init_ecs()
{
	data.ecs = ecs_init();
	ecs_world_t	*ecs = data.ecs;

	setup_phases(ecs);
	setup_tags(ecs);
	setup_components(ecs);

	ECS_SYSTEM(ecs, prepare_draw, PreDraw, 0);
	ECS_SYSTEM(ecs, prepare_draw2D, PreDraw2D, 0);
	ECS_SYSTEM(ecs, end_draw2D, PostDraw2D, 0);
	ECS_SYSTEM(ecs, end_draw, PostDraw, 0);

	ecs_query_t *colliders = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ ecs_id(Position) },
			{ ecs_id(Collider) }
		}
	});

	ecs_query_t *colliders_health = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ ecs_id(Position) },
			{ ecs_id(Collider) }, // Maybe dont care about collider,
			{ ecs_id(Health) }
		}
	});

	// Draw Systems
	ECS_SYSTEM(ecs, render_tiles, OnDraw2D, Position, Tile);
	ECS_SYSTEM(ecs, render_health, OnDraw2D, Position, Health);
	ECS_SYSTEM(ecs, flash_color, OnDraw2D, Position, Tile, FlashColor);
	ECS_SYSTEM(ecs, render_ui, OnDraw, 0);

	// Update Systems
	ECS_SYSTEM(ecs, input_player, PreUpdate, Dir, Player);
	ECS_SYSTEM(ecs, camera_follow_player, PostUpdate, Position, Player);
	ECS_SYSTEM(ecs, despawn, PostUpdate, Despawn);

	ecs_entity_t move_sys = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "Move",
			.add  = {ecs_dependson(OnUpdate)}
		}),
		.query.filter.terms = {
			{ecs_id(Position)},
			{ecs_id(Dir)},
		},
    .callback = move,
		.ctx = colliders
	});

	ecs_entity_t attack_sys = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "Attack",
			.add  = {ecs_dependson(OnUpdate)}
		}),
		.query.filter.terms = {
			{ecs_id(Attack)}
		},
		.callback = attack,
		.ctx = colliders_health
	});

	ecs_observer(ecs, {
		.filter.terms = { { ecs_id(Collider)}},
    .events = EcsOnAdd,
    .callback = on_new_collider,
	.ctx = colliders
	});

	// ECS_SYSTEM(ecs, pathfind, OnUpdate, Position, Target, Path);
	ecs_entity_t path_find_to_target = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "Pathfind",
			.add  = {ecs_dependson(OnUpdate)}
		}),
		.query.filter.terms = {
			{ecs_id(Position)},
			{ecs_id(Path)},
			{ecs_pair(TargetFollow, EcsWildcard)}
		},
		.callback = pathfind
	});

	ECS_SYSTEM(ecs, render_colliders_map, OnDraw2D, 0);
	ECS_SYSTEM(ecs, render_pathfind, OnDraw2D, Path);

	ecs_entity_t	map = ecs_entity(ecs, { .name = "GameMap" });
	ecs_set(ecs, map, Arr2D, {NULL});
	//  ecs_lookup(world, "GameMap");


	//Test entitys
	for (int i = 0; i <= data.map_bounds.y; i++)
	{
		ecs_entity_t	wall = ecs_new_id(ecs);
		ecs_set(ecs, wall, Position, {-1, i});
		ecs_set(ecs, wall, Tile, {49});
		ecs_add(ecs, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.y; i++)
	{
		ecs_entity_t	wall = ecs_new_id(ecs);
		ecs_set(ecs, wall, Position, {data.map_bounds.x + 1, i});
		ecs_set(ecs, wall, Tile, {49});
		ecs_add(ecs, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.x; i++)
	{
		ecs_entity_t	wall = ecs_new_id(ecs);
		ecs_set(ecs, wall, Position, {i, -1});
		ecs_set(ecs, wall, Tile, {49});
		ecs_add(ecs, wall, Collider);
	}
	for (int i = 0; i <= data.map_bounds.x; i++)
	{
		ecs_entity_t	wall = ecs_new_id(ecs);
		ecs_set(ecs, wall, Position, {i, data.map_bounds.y + 1});
		ecs_set(ecs, wall, Tile, {49});
		ecs_add(ecs, wall, Collider);
	}
	ecs_entity_t	p = ecs_entity(ecs, { .name = "Player" });
	ecs_entity_t	e = ecs_new_id(ecs);
	ecs_set(ecs, p, Position, {10, 10});
	ecs_set(ecs, p, Tile, {21});
	ecs_set(ecs, p, Dir, {0});
	ecs_set(ecs, p, Health, {3});
	ecs_add(ecs, p, Player);
	ecs_add(ecs, p, Collider);

	ecs_set(ecs, e, Position, {22, 10});
	ecs_set(ecs, e, Tile, {41});
	ecs_set(ecs, e, Health, {3});
	ecs_set(ecs, e, Dir, {0, 0});
	ecs_set(ecs, e, Path, {NULL, NULL, NULL});
	ecs_add_pair(ecs, e, TargetFollow, p);
	ecs_add(ecs, e, Collider);

	fill_map(ecs, colliders, map);
}

static void	 setup_tags(ecs_world_t *ecs)
{
	ECS_TAG_DEFINE(ecs, Player);
	ECS_TAG_DEFINE(ecs, Enemy);
	ECS_TAG_DEFINE(ecs, Collider);
	ECS_TAG_DEFINE(ecs, Despawn);
	ECS_TAG_DEFINE(ecs, TargetFollow);
}

static void	 setup_components(ecs_world_t *ecs)
{
	ECS_COMPONENT_DEFINE(ecs, Position);
	ECS_COMPONENT_DEFINE(ecs, Tile);
	ECS_COMPONENT_DEFINE(ecs, Dir);
	ECS_COMPONENT_DEFINE(ecs, Health);
	ECS_COMPONENT_DEFINE(ecs, FlashColor);
	ECS_COMPONENT_DEFINE(ecs, Attack);
	ECS_COMPONENT_DEFINE(ecs, Arr2D);
	ECS_COMPONENT_DEFINE(ecs, Path);
}

static void	 setup_phases(ecs_world_t *ecs)
{
	PreUpdate = ecs_new_w_id(ecs, EcsPhase);
	OnUpdate = ecs_new_w_id(ecs, EcsPhase);
	PostUpdate = ecs_new_w_id(ecs, EcsPhase);
	PreDraw = ecs_new_w_id(ecs, EcsPhase);
	PreDraw2D = ecs_new_w_id(ecs, EcsPhase);
	OnDraw2D = ecs_new_w_id(ecs, EcsPhase);
	PostDraw2D = ecs_new_w_id(ecs, EcsPhase);
	OnDraw = ecs_new_w_id(ecs, EcsPhase);
	PostDraw = ecs_new_w_id(ecs, EcsPhase);
	ecs_add_pair(ecs, OnUpdate, EcsDependsOn, PreUpdate);
	ecs_add_pair(ecs, PostUpdate, EcsDependsOn, OnUpdate);
	ecs_add_pair(ecs, PreDraw, EcsDependsOn, PostUpdate);
	ecs_add_pair(ecs, PreDraw2D, EcsDependsOn, PreDraw);
	ecs_add_pair(ecs, OnDraw2D, EcsDependsOn, PreDraw2D);
	ecs_add_pair(ecs, PostDraw2D, EcsDependsOn, OnDraw2D);
	ecs_add_pair(ecs, OnDraw, EcsDependsOn, OnDraw2D);
	ecs_add_pair(ecs, PostDraw, EcsDependsOn, OnDraw);
}
