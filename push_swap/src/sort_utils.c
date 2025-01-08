#include "push_swap.h"

void	ft_error(void)
{
	write (2, "Error\n", 6);
	exit(1);
}

int	min(t_Node *a)				// Min int of the stack
{
	t_Node	*curr;
	int		i;

	curr = a;
	i = curr->x;
	while (curr)
	{
		if (curr->x < i)
			i = curr->x;
		curr = curr->next;
	}
	return (i);
}

int	max(t_Node *a)				// Max int of the stack
{
	t_Node	*curr;
	int		i;

	curr = a;
	i = curr->x;
	while (curr)
	{
		if (curr->x > i)
			i = curr->x;
		curr = curr->next;
	}
	return (i);
}

// This function returns the size of the stack.
int	list_size(t_Node *a)
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
t_Node	*last_node(t_Node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
