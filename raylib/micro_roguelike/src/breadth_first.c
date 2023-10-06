#include "game.h"

static Vector2	**get_neighbors(int **grid, Vector2 grid_size, Vector2 pos);
static List	*lstfind(List *list, Vector2 *content);

List	*pathfind_breadth_first(int **grid, Vector2 grid_size, Vector2 starting_pos, Vector2 goal)
{
	Vector2	*pos = malloc(sizeof(Vector2));
	*pos = starting_pos;
	List	*frontier = lstnew(pos); // TODO keep reference of this first node and free at the end
	List	*frontier_ref = frontier;
	Vector2	*p = calloc(2, sizeof(Vector2)); // NOTE WHAT A MESS
	p[0] = *pos;
	p[1] = (Vector2) {-1, -1};
	List	*reached = lstnew(p);

	while (frontier)
	{
		Vector2	current = *((Vector2 *) frontier->content);
		if (current.x == goal.x && current.y == goal.y)
			break ;
		Vector2	**adjecents = get_neighbors(grid, grid_size, current);
		int		i = -1;
		while (adjecents[++i]) // NOTE maybe check for goal should be done here
		{
			if (lstfind(reached, adjecents[i]) == NULL && (get_array(grid, *adjecents[i]) == 0 || Vector2Compare(goal, *adjecents[i])))
			{
				Vector2	*a = calloc(2, sizeof(Vector2));
				a[0] = *adjecents[i];
				a[1] = *((Vector2 *) frontier->content);
				lstadd_back(&frontier, lstnew(adjecents[i]));
				lstadd_back(&reached, lstnew(a));
			}
			else
				free(adjecents[i]);
		}
		frontier = frontier->next;
	}
	lstclear(&frontier_ref, free);
	return (reached);
}

List	*breadth_first_search(int **grid, Vector2 grid_size, Vector2 starting_pos)
{
	Vector2	*pos = malloc(sizeof(Vector2));
	*pos = starting_pos;
	List	*frontier = lstnew(pos); // NOTE not being freed but this func should not really be used
	List	*reached = lstnew(pos);

	while (frontier)
	{
		Vector2	**adjecents = get_neighbors(grid, grid_size, *((Vector2 *) frontier->content));
		int		i = -1;
		while (adjecents[++i])
		{
			if (lstfind(reached, adjecents[i]) == NULL)
			{
				lstadd_back(&frontier, lstnew(adjecents[i]));
				lstadd_back(&reached, lstnew(adjecents[i]));
			}
			else
				free(adjecents[i]);
		}
		frontier = frontier->next;
	}
	return (reached);
}

static Vector2	**get_neighbors(int **grid, Vector2 grid_size, Vector2 pos)
{
	Vector2	**neighbors = calloc(5, sizeof(Vector2 *));
	Vector2	add[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int		i = -1;
	int		k = 0;

	while (++i < 4)
	{
		Vector2	new_pos = Vector2Add(pos, add[i]);
		if (new_pos.x < 0 || new_pos.x >= grid_size.x || new_pos.y < 0 || new_pos.y >= grid_size.y)
			continue ;
		Vector2	*neighbor = malloc(sizeof(Vector2));
		*neighbor = new_pos;
		neighbors[k] = neighbor;
		k++;
	}
	return (neighbors);
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
