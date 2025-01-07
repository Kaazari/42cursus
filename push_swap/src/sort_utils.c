#include "push_swap.h"

void	print_list(Node *a)
{
	printf("Current list:  ");
	Node *y = a;
	while (y != NULL)
	{
		printf("%i   ", y->x);
		y = y->next;
	}
	printf("\n");
}

int min(Node *a)				// Min int of the stack
{
	Node *curr = a;
	int i = curr->x;
	while (curr)
	{
		if (curr->x < i)
			i = curr->x;
		curr = curr->next;
	}
	return (i);
}

int	max(Node *a)				// Max int of the stack
{
	Node *curr = a;
	int i = curr->x;
	while (curr)
	{
		if (curr->x > i)
			i = curr->x;
		curr = curr->next;
	}
	return (i);
}

// This function returns the size of the stack.
int	list_size(Node *a)
{
	int	i;

	i = 0;
	while (a)
	{
		a = a->next;
		i++;
	}
	return (i);
}

// This function returns the last element of the stack.
Node	*last_node(Node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
