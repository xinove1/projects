#include "game.h"

ECS_COMPONENT_DECLARE(Tile);
ECS_COMPONENT_DECLARE(Health);
ECS_COMPONENT_DECLARE(FlashColor);
ECS_COMPONENT_DECLARE(Attack);
ECS_COMPONENT_DECLARE(TimerDeath);
ECS_COMPONENT_DECLARE(EnergyLevel);
ECS_COMPONENT_DECLARE(EnemyState);
ECS_COMPONENT_DECLARE(LineOfSight);

ECS_TAG_DECLARE(Despawn);
ECS_TAG_DECLARE(Player);
ECS_TAG_DECLARE(Enemy);
ECS_TAG_DECLARE(Collider);
ECS_TAG_DECLARE(TargetFollow);

ecs_query_t	*COLLIDERS_QUERY;
ecs_query_t	*COLLIDERS_HEALTH_QUERY;

static void	setup_tags(ecs_world_t *ecs);
static void	setup_components(ecs_world_t *ecs);
static void	on_update(ecs_iter_t *it);
static void	test_entitys(ecs_world_t *ecs);
static int flecs_entity_compare(ecs_entity_t e1, const void *ptr1, ecs_entity_t e2, const void *ptr2);

void	init_ecs()
{
	data.ecs = ecs_init();
	ecs_world_t	*ecs = data.ecs;

	ECS_IMPORT(ecs, RaylibPipeline);
	ECS_IMPORT(ecs, BasicComponents);
	ECS_IMPORT(ecs, Pathfind);
	set_camera(&data.camera);
	set_raycast_entity_check_func(&check_collision);

	setup_tags(ecs);
	setup_components(ecs);

	COLLIDERS_QUERY = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ ecs_id(Position) },
			{ ecs_id(Collider) }
		}
	});

	COLLIDERS_HEALTH_QUERY = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ ecs_id(Position) },
			{ ecs_id(Collider) }, // Maybe dont care about collider,
			{ ecs_id(Health) }
		}
	});

	ecs_query_t *on_update_systems = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ EcsSystem },
			{ ecs_pair(EcsDependsOn, OnUpdate)}
		},
		.order_by = flecs_entity_compare
	});

	ecs_query_t *energy_level_query = ecs_query_init(ecs, &(ecs_query_desc_t){
		.filter.terms = {
			{ ecs_id(EnergyLevel) },
		}
	});

	// Draw Systems
	ECS_SYSTEM(ecs, render_tiles, OnDraw2D, Position, Tile);
	ECS_SYSTEM(ecs, render_sight, OnDraw2D, Position, LineOfSight);
	ECS_SYSTEM(ecs, render_colliders_map, OnDraw2D, 0);
	ECS_SYSTEM(ecs, render_health, OnDraw2D, Position, Health);
	ECS_SYSTEM(ecs, flash_color, OnDraw2D, Position, Tile, FlashColor);
	ECS_SYSTEM(ecs, render_ui, OnDraw, 0);

	// TODO test system
	ecs_entity_t raycast_test = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "test",
			.add  = {ecs_dependson(OnDraw2D)}
		}),
		/* .query.filter.terms = { */
		/* 	{ecs_id(Attack)} */
		/* }, */
		.callback = test_raycast,
	});

	ecs_entity_t _game_loop = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "GameLoop",
			.add  = {ecs_dependson(PreUpdate)}
		}),
		/* .query.filter.terms = { */
		/* 	{ecs_id(EnergyLevel)} */
		/* }, */
		.callback = game_loop,
		.ctx = energy_level_query,
		.no_readonly = true
	});

	// Update Systems
	//ECS_SYSTEM(ecs, pathfind, OnUpdate, Position, Path);
	ECS_SYSTEM(ecs, input_player, PreUpdate, 0);
	ECS_SYSTEM(ecs, camera_follow_player, PostUpdate, Position, Player);
	ECS_SYSTEM(ecs, despawn, PostUpdate, Despawn);

	ecs_entity_t on_update_sys = ecs_system(ecs, {
		.entity = ecs_entity(ecs,{
			.name =  "OnUpdate",
			.add  = {ecs_dependson(OnUpdateReal)}
		}),
		.callback = on_update,
		.ctx = on_update_systems
	});

	ECS_SYSTEM(ecs, update_colliders_map, PostUpdate);

	ecs_entity_t	player_action = ecs_entity(ecs, { .name =  "PlayerAction" });
	ecs_set(ecs, player_action, Bool, {false});
	ecs_entity_t	map = ecs_entity(ecs, { .name = "GameMap" });
	ecs_set(ecs, map, Arr2D, {NULL});

	ecs_entity_t	p = ecs_entity(ecs, { .name = "Player" });
	ecs_set(ecs, p, Position, {25, 10});
	ecs_set(ecs, p, EnergyLevel, {0, 10});
	ecs_set(ecs, p, Tile, {21, 0});
	ecs_set(ecs, p, Dir, {0});
	ecs_set(ecs, p, Health, {3});
	ecs_add(ecs, p, Player);
	ecs_add(ecs, p, Collider);
	printf("json: \n %s\n", ecs_entity_to_json(ecs, p, NULL));
	//load_level(ecs);
	//load_grid(ecs);
	test_entitys(ecs);
}

static void	test_entitys(ecs_world_t *ecs)
{
	ecs_entity_t	p = ecs_lookup(ecs, "Player");
	ecs_entity_t	e = ecs_new_id(ecs);

	ecs_set(ecs, e, Position, {22, 10});
	ecs_set(ecs, e, EnergyLevel, {0, 10});
	ecs_set(ecs, e, Tile, {41, 0});
	ecs_set(ecs, e, EnemyState, {PATROL});
	ecs_set(ecs, e, LineOfSight, {4});
	ecs_set(ecs, e, Health, {3});
	ecs_set(ecs, e, Dir, {0, 0});
	ecs_set(ecs, e, Path, {NULL, NULL, NULL});
	ecs_add_pair(ecs, e, TargetFollow, p);
	ecs_add(ecs, e, Collider);

	place_game_border(ecs);
	ecs_entity_t	game_map = ecs_lookup(ecs, "GameMap");
	fill_map(ecs, COLLIDERS_QUERY, game_map);
}

static void	on_update(ecs_iter_t *it)
{
	bool	*player_action_wait = ecs_get_mut(it->world, ecs_lookup(it->world, "PlayerAction"), Bool);
	if (*player_action_wait)
		return ;
	ecs_iter_t	iter = ecs_query_iter(it->world, it->ctx);
	while (ecs_query_next(&iter))
	{
		for (int i = 0; i < iter.count; i++)
		{
			ecs_run(it->world, iter.entities[i], it->delta_time, NULL);
			//printf("%s\n", ecs_get_name(it->world, iter.entities[i]));
		}
	}
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
	ECS_COMPONENT_DEFINE(ecs, Tile);
	ECS_COMPONENT_DEFINE(ecs, Health);
	ECS_COMPONENT_DEFINE(ecs, FlashColor);
	ECS_COMPONENT_DEFINE(ecs, Attack);
	ECS_COMPONENT_DEFINE(ecs, TimerDeath);
	ECS_COMPONENT_DEFINE(ecs, EnergyLevel);
	ECS_COMPONENT_DEFINE(ecs, EnemyState);
	ECS_COMPONENT_DEFINE(ecs, LineOfSight);
}

static int flecs_entity_compare(ecs_entity_t e1, const void *ptr1, ecs_entity_t e2, const void *ptr2)
{
    (void)ptr1;
    (void)ptr2;
    return (e1 > e2) - (e1 < e2);
}
