#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#ifndef ARENA_ALLOC_H_
# define ARENA_ALLOC_H_
# ifndef ARENA_BLOCK_SIZE
#  define ARENA_BLOCK_SIZE 1024
# endif

typedef struct A_free
{
	void			*mem;
	struct A_free	*next;
} A_free;

typedef struct Arena
{
	char	*mem_begin;
	char	*mem_end;
	char	*pos;
	size_t	chunk_sz; // What multiple of this size will the alloctor use
	A_free	*freed;
} Arena;

Arena	*ArenaCreate(size_t chunk);
void	ArenaDestroy(Arena *arena);
void	*ArenaAlloc(Arena *arena, size_t size);
void	*ArenaAllocZero(Arena *arena, size_t size);
size_t	ArenaGetPos(Arena *arena);
//void	ArenaPop(Arena *arena, size_t size);

# define PushArray(arena, type, count) (type *)ArenaPush((arena), sizeof(type)*(count))
# define PushArrayZero(arena, type, count) (type *)ArenaPushZero((arena), sizeof(type)*(count))
# define PushStruct(arena, type) PushArray((arena), (type), 1)
# define PushStructZero(arena, type) PushArrayZero((arena), (type), 1)


inline Arena	*ArenaCreate(size_t chunk)
{
	Arena	*arena = (Arena*)malloc(sizeof(Arena));

	arena->mem_begin = (char *)malloc(ARENA_BLOCK_SIZE);
	arena->mem_end = arena->mem_begin + ARENA_BLOCK_SIZE;
	arena->pos = arena->mem_begin;
	arena->chunk_sz = chunk;
	arena->freed = NULL;
	return (arena);
}

inline void	ArenaDestroy(Arena *arena)
{
	A_free	*tmp = arena->freed;
	while (tmp)
	{
		arena->freed = tmp;
		tmp = tmp->next;
		free(arena->freed);
	}
	free(arena->mem_begin);
	free(arena);
}

inline void	*ArenaAlloc(Arena *arena, size_t size)
{
	void	*mem = NULL;
	size_t	size_alloc;//TODO

	assert((arena->pos + size_alloc) > arena->mem_end);
	if (!arena->freed && size_alloc > arena->chunk_sz)
	{
		mem = arena->pos;
		arena->pos = arena->pos + size_alloc;
	}
	else
	{
		A_free	*tmp = arena->freed;
		mem = tmp->mem;
		arena->freed = tmp->next;
		free(tmp);
	}
	return (mem);
}

#endif // ARENA_ALLOC_H_
