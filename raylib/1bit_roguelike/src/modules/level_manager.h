#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

# include "../includes.h"
# include "basic_components_module.h"

ecs_entity_t	get_player(ecs_world_t	*ecs);
Arr2D	get_map_arr(ecs_world_t	*ecs);

#endif // LEVEL_MANAGER_H_
