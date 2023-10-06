#include "game.h"

void	update_enemys()
{
	move_enemys();

	data.player_turn = true;
}

void	move_enemys()
{
	List	*enemy = data.enemys;

	while (enemy)
	{
		move_enemy((Enemy *) enemy->content);
		enemy = enemy->next;
	}
}

void	move_enemy(Enemy *enemy)
{
	//printf("enemy path %f,%f\n", enemy->path[enemy->path_pos].x, enemy->path[enemy->path_pos].y);
	if (enemy->path == NULL)
		return ;
	Vector2	new_pos = Vector2Add(enemy->path[enemy->path_pos], enemy->pos);
	if (get_array(data.map.interactives, new_pos) == 0)
		move(data.map.interactives, &enemy->pos, new_pos, ENEMY);
	else if (get_array(data.map.interactives, new_pos) == PLAYER)
		data.player.health -= 1;
	else
	{
		printf("ERROR: enemy tryng to move to a wall (maybe)\n"); // NOTE Catch possible errors on path finding, remove later
		printf("tried to move to: %f,%f\n", new_pos.x, new_pos.y);
	}
	if (enemy->path_pos + 1 == enemy->path_size)
	{
		free(enemy->path);
		enemy->path = NULL;
	}
	enemy->path_pos++;
}

void	spawn_enemy(int health, Vector2 pos)
{
	Enemy	*enemy = calloc(3, sizeof(Enemy));
	enemy->health = 5;
	enemy->pos = (Vector2) {10,10};
	set_array(data.map.interactives, pos, ENEMY);
	pathfind_test(enemy, data.player.pos);
	lstadd_back(&data.enemys, lstnew(enemy));
}

static void	free_enemy(void	*ptr)
{
	Enemy	*enemy = ptr;
	if (enemy->path)
		free(enemy->path);
	free(enemy);
}
