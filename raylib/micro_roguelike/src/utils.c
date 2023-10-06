#include "game.h"

int	get_array(int	**array, Vector2 pos)
{
	return (array[(int)pos.y][(int)pos.x]);
}

void	set_array(int	**array, Vector2 pos, int new_value)
{
	array[(int)pos.y][(int)pos.x] = new_value;
}

int	Vector2Compare(Vector2 vec1, Vector2 vec2) // NOTE rename?
{
	return (vec1.x == vec2.x &&  vec1.y == vec2.y);
}

void	move(int **arr, Vector2 *to_move, Vector2 new_pos, int value)
{
	set_array(arr, new_pos, value);
	set_array(arr, *to_move, 0);
	*to_move = new_pos;
}
