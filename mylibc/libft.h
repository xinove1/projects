#ifndef LIBFT_H_
# define LIBFT_H_
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <assert.h>

# ifndef ARENA_BLOCK_SIZE
#  define ARENA_BLOCK_SIZE 1024
# endif


// NOTE from untangling lifetimes, dont really remember why i got them
/* # define PushArray(arena, type, count) (type *)ArenaPush((arena), sizeof(type)*(count)) */
/* # define PushArrayZero(arena, type, count) (type *)ArenaPushZero((arena), sizeof(type)*(count)) */
/* # define PushStruct(arena, type) PushArray((arena), (type), 1) */
/* # define PushStructZero(arena, type) PushArrayZero((arena), (type), 1) */

typedef struct List
{
	void		*content;
	struct List	*next;
} List;

typedef struct
{
	char	*mem_begin;
	char	*mem_end;
	char	*pos;
	size_t	chunk_sz;
	List	*freed;
} Arena;

// Arena
Arena	*arena_create(size_t chunk_size);
Arena	*arena_create_sized(size_t chunk_size, size_t mem_size_scalar);
void	arena_destroy(Arena *arena);
void	*linear_alloc(Arena *arena, size_t size); // Linear
void	*pool_alloc(Arena *arena); // Pool
void	pool_free(Arena *arena, void *mem);
void	arena_resize(Arena *arena);
void	arena_clean(Arena *arena);

// List
List	*lstnew(Arena *arena, void *content);
void	lstadd_front(List **lst, List *new_list);
int		lstsize(List *lst);
List	*lstlast(List *lst);
void	lstadd_back(List **list, List *new_list);
void	lstdelone(List *lst, void (*del)(void*));
void	lstclear(List **lst, void (*del)(void*));
void	lstiter(List *lst, void (*f)(void *));
List	*lstmap(Arena *arena, List *lst, void *(*f)(void *), void (*del)(void *));


#endif // LIBFT_H_
