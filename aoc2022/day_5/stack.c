#include "stack.h"
#include <stdio.h>

t_stack	*StackNew(char crate)
{
	t_stack	*new = malloc(sizeof(t_stack));
	new->next = NULL;
	new->previous = NULL;
	new->crate = crate;
	return (new);
}

void	StackAddBack(t_stack **stack, t_stack *new_item)
{
	t_stack	*i;

	if (!*stack)
		*stack = new_item;
	else
	{
		i = StackGetLast(*stack);
		i->next = new_item;
		new_item->previous = i;
	};
}

void	StackAddFront(t_stack **stack, t_stack *new_item)
{
	new_item->next = *stack;
	(*stack)->previous = new_item;
}

t_stack	*StackGetLast(t_stack *stack)
{
	t_stack	*i;

	if (!stack)
		return (NULL);
	i = stack;
	while (i->next)
		i = i->next;
	return (i);
}

void	StackPrint(t_stack *stack)
{
	t_stack	*i;

	i = stack;
	while (i)
	{
		printf("[%c], ", i->crate);
		i = i->next;
	}
	printf("\n");
}

void	StackPrintBackwords(t_stack *stack_last)
{
	t_stack	*i;

	i = stack_last;
	while (i)
	{
		printf("[%c]\n", i->crate);
		i = i->previous;
	}
}

int	StackSize(t_stack *stack)
{
	t_stack	*i;
	int		size;

	i = stack;
	size = 1;
	while (i->next)
	{
		i = i->next;
		size++;
	}
	return (size);
}

// Move qty items from stack from to to
void	StackMoveManyOrder(t_stack **from, t_stack **to, int	qty)
{
	t_stack	*stack;

	if (!*from)
	{
		printf("qty: %d\n", qty);
		printf("Can't move from empty stack\n");
		return ;
	}
	if (qty > StackSize(*from))
	{
		printf("Quantity to move is bigger than stack from.\n");
		return ;
	}
	stack = StackGetLast(*from);
	qty--;
	while (qty > 0)
	{
		if (!stack->previous)
			break ;
		stack = stack->previous;
		qty--;
	}
	if (stack->previous)
	{
		stack->previous->next = NULL;
		stack->previous = NULL;
	}
	else
		*from = NULL;
	StackAddBack(to, stack);
}

void	StackMoveMany(t_stack **from, t_stack **to, int	qty)
{
	if (!*from)
	{
		printf("qty: %d\n", qty);
		printf("Can't move from empty stack\n");
		return ;
	}
	if (qty > StackSize(*from))
	{
		printf("Quantity to move is bigger than stack from.\n");
		return ;
	}
	while (qty > 0)
	{
		StackMove(from, to);
		qty--;
	}
}

void	StackMove(t_stack	**from, t_stack **to)
{
	t_stack	*stack;

	if (!*from)
	{
		printf("Can't move from empty stack\n");
		return ;
	}
	stack = StackGetLast(*from);
	if (stack->previous)
	{
		stack->previous->next = NULL;
		stack->previous = NULL;
	}
	else
		*from = NULL;
	StackAddBack(to, stack);
}

void	StackPrintMany(t_stack **cargo)
{
	for (int j = 0; cargo[j]; j++)
	{
		printf("[%d]: ", j);
		StackPrint(cargo[j]);
	}
}
