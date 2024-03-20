#ifndef REC_COLLISION_H_
#define REC_COLLISION_H_

# include "raylib.h"
# include "raymath.h"

bool	CheckCollisionRayRec(Vector2 origin, Vector2 dir, Rectangle rec,
							 Vector2 *contact_point, Vector2 *contact_normal, float *t_hit_near);
bool	CheckCollisionDynamicRectRect(Vector2 origin, Rectangle rec, Vector2 vel, Rectangle target,
									  Vector2 *contact_point, Vector2 *contact_normal,
									  float *contact_time, float delta_time);

#endif // REC_COLLISION_H_
