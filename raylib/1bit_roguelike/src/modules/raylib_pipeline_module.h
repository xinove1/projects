#ifndef RAYLIB_PIPELINE_MODULE_H_
#define RAYLIB_PIPELINE_MODULE_H_

#include "../includes.h"

// Ids
extern ECS_DECLARE(PreUpdate);
extern ECS_DECLARE(OnUpdate);
extern ECS_DECLARE(OnUpdateReal);
extern ECS_DECLARE(PostUpdate);
extern ECS_DECLARE(PreDraw);
extern ECS_DECLARE(PreDraw2D);
extern ECS_DECLARE(OnDraw2D);
extern ECS_DECLARE(PostDraw2D);
extern ECS_DECLARE(OnDraw);
extern ECS_DECLARE(PostDraw);

void	prepare_draw(ecs_iter_t	*it);
void	prepare_draw2D(ecs_iter_t *it);
void	end_draw2D(ecs_iter_t *it);
void	end_draw(ecs_iter_t *it);

void	RaylibPipelineImport(ecs_world_t *ecs);
void	set_camera(Camera2D *camera);
void	set_background_color(Color color);


#endif // RAY_PIPELINE_H_
