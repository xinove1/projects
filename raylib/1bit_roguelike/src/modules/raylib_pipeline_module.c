#include "raylib_pipeline_module.h"

ECS_DECLARE(PreUpdate);
ECS_DECLARE(OnUpdate);
ECS_DECLARE(OnUpdateReal);
ECS_DECLARE(PostUpdate);
ECS_DECLARE(PreDraw);
ECS_DECLARE(PreDraw2D);
ECS_DECLARE(OnDraw2D);
ECS_DECLARE(PostDraw2D);
ECS_DECLARE(OnDraw);
ECS_DECLARE(PostDraw);

static void	 setup_phases(ecs_world_t *ecs);

static Camera2D	*_camera = NULL;
static Color	_color = RAYWHITE;

void RaylibPipelineImport(ecs_world_t *ecs)
{
	ECS_MODULE(ecs, RaylibPipeline);

	setup_phases(ecs);

	ECS_SYSTEM(ecs, prepare_draw, PreDraw, 0);
	ECS_SYSTEM(ecs, prepare_draw2D, PreDraw2D, 0);
	ECS_SYSTEM(ecs, end_draw2D, PostDraw2D, 0);
	ECS_SYSTEM(ecs, end_draw, PostDraw, 0);
}

static void	 setup_phases(ecs_world_t *ecs)
{
	PreUpdate = ecs_new_w_id(ecs, EcsPhase);
	OnUpdate = ecs_new_id(ecs);
	OnUpdateReal = ecs_new_w_id(ecs, EcsPhase);
	PostUpdate = ecs_new_w_id(ecs, EcsPhase);
	PreDraw = ecs_new_w_id(ecs, EcsPhase);
	PreDraw2D = ecs_new_w_id(ecs, EcsPhase);
	OnDraw2D = ecs_new_w_id(ecs, EcsPhase);
	PostDraw2D = ecs_new_w_id(ecs, EcsPhase);
	OnDraw = ecs_new_w_id(ecs, EcsPhase);
	PostDraw = ecs_new_w_id(ecs, EcsPhase);
	ecs_add_pair(ecs, OnUpdateReal, EcsDependsOn, PreUpdate);
	ecs_add_pair(ecs, PostUpdate, EcsDependsOn, OnUpdateReal);
	ecs_add_pair(ecs, PreDraw, EcsDependsOn, PostUpdate);
	ecs_add_pair(ecs, PreDraw2D, EcsDependsOn, PreDraw);
	ecs_add_pair(ecs, OnDraw2D, EcsDependsOn, PreDraw2D);
	ecs_add_pair(ecs, PostDraw2D, EcsDependsOn, OnDraw2D);
	ecs_add_pair(ecs, OnDraw, EcsDependsOn, OnDraw2D);
	ecs_add_pair(ecs, PostDraw, EcsDependsOn, OnDraw);
}

void	prepare_draw(ecs_iter_t	*it)
{
	(void) it;
	BeginDrawing();
	ClearBackground(_color);
}

void	prepare_draw2D(ecs_iter_t *it)
{
	(void) it;

	assert(_camera != NULL);
	BeginMode2D(*_camera);
}

void	end_draw2D(ecs_iter_t *it)
{
	(void) it;

	EndMode2D();
}

void	end_draw(ecs_iter_t *it)
{
	(void) it;

	EndDrawing();
}

void	set_camera(Camera2D *camera)
{
	_camera = camera;
}

void	set_background_color(Color color)
{
	_color = color;
}
