#include "game.h"

void	print_arr2d(Arr2D arr)
{
	for (int y = 0; y < arr.size.y; y++)
	{
		for (int x = 0; x < arr.size.x; x++)
		{
			printf("%d ", arr.arr[y][x]);
		}
		printf("\n");
	}
}
