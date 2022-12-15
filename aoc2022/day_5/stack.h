#ifndef STACK_H
# define STACK_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../libft/libft.h"


typedef struct s_stack
{
	char			crate;
	struct s_stack	*next;
	struct s_stack	*previous;
}t_stack;

t_stack	*StackNew(char crate);
t_stack	*StackGetLast(t_stack *stack);
void	StackAddBack(t_stack **stack, t_stack *new_item);
void	StackAddFront(t_stack **stack, t_stack *new_item);
void	StackPrint(t_stack *stack);
void	StackPrintBackwords(t_stack *stack_last);
void	StackMoveMany(t_stack **from, t_stack **to, int	qty);
void	StackPrintMany(t_stack **cargo);
void	StackMove(t_stack	**from, t_stack **to);
void	StackMoveManyOrder(t_stack **from, t_stack **to, int qty);

#endif
