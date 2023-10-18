#include "game.h"

Position	Vector2ToPos(Vector2 v)
{
	return ((Position) {v.x, v.y});
}

Vector2		PosToVector2(Position p)
{
	return ((Vector2) {p.x, p.y});
}


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
