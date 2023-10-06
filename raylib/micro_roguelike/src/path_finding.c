#include "game.h"

static List	*lstfind(List *list, Vector2 *content);
static void	build_path_enemy(Enemy *enemy, List *lstpath);

void	pathfind_test(Enemy *enemy, Vector2 target)
{
	List	*list = pathfind_breadth_first(data.map.interactives, data.map.size, enemy->pos, target);
	List	*current_node = lstfind(list, &target);
	List	*path = lstnew(current_node->content);

	while (current_node)
	{
		Vector2	from = ((Vector2 *)current_node->content)[1];
		Vector2	current = ((Vector2 *)current_node->content)[0];
		lstadd_front(&path, lstnew(current_node->content));
		if (from.x == -1)
			break ;
		current_node = lstfind(list, &from);
	}
	build_path_enemy(enemy, path);
	lstclear(&path, NULL);
	lstclear(&list, free);
}

static void	build_path_enemy(Enemy *enemy, List *path_list)
{
	int		path_size = lstsize(path_list) - 2; // NOTE eh ne
	Vector2	*path = calloc(path_size, sizeof(Vector2));
	enemy->path = path;
	enemy->path_size = path_size;
	enemy->path_pos = 0;

	Vector2	from = *((Vector2 *) path_list->content);
	List	*lstpath = path_list;
	lstpath = lstpath->next;
	int		i = 0;
	while (lstpath && i < path_size)
	{
		Vector2	current = *((Vector2 *) lstpath->content);
		Vector2	diff = Vector2Subtract(current, from);
		path[i] = diff;
		from = current;
		i++;
		lstpath = lstpath->next;
	}
}

static List	*lstfind(List *list, Vector2 *content)
{
	while (list)
	{
		Vector2	*v = (Vector2 *)list->content;
		if (v->x == content->x && v->y == content->y)
			return (list);
		list = list->next;
	}
	return (NULL);
}
