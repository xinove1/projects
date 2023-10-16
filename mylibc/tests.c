#include "libft.h"

int	main()
{
	Arena *a = arena_create(20);
	printf("asoeuth: %p\n", a->freed);
	pool_alloc(a);
}
