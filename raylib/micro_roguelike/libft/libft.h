#ifndef LIBFT_H_
# define LIBFT_H_
# include <stdlib.h>

typedef struct List
{
	void		*content;
	struct List	*next;
}					List;

List	*lstnew(void *content);
void	lstadd_front(List **lst, List *new_list);
int		lstsize(List *lst);
List	*lstlast(List *lst);
void	lstadd_back(List **list, List *new_list);
void	lstdelone(List *lst, void (*del)(void*));
void	lstclear(List **lst, void (*del)(void*));
void	lstiter(List *lst, void (*f)(void *));
List	*lstmap(List *lst, void *(*f)(void *), void (*del)(void *));


#endif // LIBFT_H_
