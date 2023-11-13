#include "libft.h"

static void	arena_push_freed(Arena *arena);

Arena	*arena_create(size_t chunk_size)
{
	Arena	*arena = (Arena*) malloc(sizeof(Arena));

	arena->mem_begin = (char *) malloc(ARENA_BLOCK_SIZE);
	arena->mem_end = arena->mem_begin + ARENA_BLOCK_SIZE;
	arena->pos = arena->mem_begin;
	arena->chunk_sz = chunk_size;
	arena->freed = NULL;
	if (chunk_size != 0)
	{
		assert(chunk_size >= sizeof(List));
		arena_push_freed(arena);
	}
	return (arena);
}

Arena	*arena_create_sized(size_t chunk_size, size_t mem_size_scalar)
{
	Arena	*arena = (Arena*) malloc(sizeof(Arena));

	arena->mem_begin = (char *) malloc(ARENA_BLOCK_SIZE * mem_size_scalar);
	arena->mem_end = arena->mem_begin + ARENA_BLOCK_SIZE * mem_size_scalar;
	arena->pos = arena->mem_begin;
	arena->chunk_sz = chunk_size;
	arena->freed = NULL;
	if (chunk_size != 0)
	{
		assert(chunk_size >= sizeof(List));
		arena_push_freed(arena);
	}
	return (arena);
}

void	arena_destroy(Arena *arena)
{
	free(arena->mem_begin);
	free(arena);
}

void	*linear_alloc(Arena *arena, size_t size)
{
	assert(!arena->chunk_sz);
	void	*mem = NULL;
	size_t	size_alloc;

	size_alloc = size;

	if (arena->pos + size_alloc > arena->mem_end)
		arena_resize(arena);
	mem = arena->pos;
	memset(mem, 0, size_alloc);
	arena->pos += size_alloc;
	return (mem);
}

void	*pool_alloc(Arena *arena)
{
	assert(arena->chunk_sz);
	void	*mem = NULL;

	mem = arena->freed;
	assert(mem != NULL);
	arena->freed = arena->freed->next;
	return (mem);
}

void	pool_free(Arena *arena, void *mem)
{
	assert((char *) mem >= arena->mem_begin && (char *) mem <= arena->mem_end);

	memset(mem, 0, arena->chunk_sz);
	List	*node = mem;
	node->next = arena->freed;
	arena->freed = node;
}

void	arena_clean(Arena *arena)
{
	memset(arena->mem_begin, 0, arena->pos - arena->mem_begin);
	arena->pos = arena->mem_begin;
	if (arena->chunk_sz)
		arena_push_freed(arena);
}

static void	arena_push_freed(Arena *arena)
{
	int	size = (arena->mem_end - arena->mem_begin ) / arena->chunk_sz;

	for (int i = 0; i < size; i++)
	{
		List *node = (List *)&arena->mem_begin[i * arena->chunk_sz];
		node->next = arena->freed;
		arena->freed = node;
	}
}

void	arena_resize(Arena *arena)
{
	assert(0 == 1);
	fprintf(stderr, "INFO: arena being resized\n");
	arena->mem_begin = realloc(arena->mem_begin, arena->mem_end - arena->mem_begin + ARENA_BLOCK_SIZE);
}
