#include "push_swap.h"

// Check if the chracter is negative
int	sign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

// add a new node at the end of the linked list
void	insert_end(t_Node **root, int value)
{
	t_Node	*new_node;
	t_Node	*curr;

	new_node = malloc(sizeof(t_Node));
	if (!new_node)
		exit(1);
	new_node->next = NULL;
	new_node->x = value;
	if (*root == NULL)
	{
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_node;
}

// This function checks if the stack is sorted.
int	sorted(t_Node *a)
{
	int	i;

	i = a->x;
	while (a)
	{
		if (i > a->x)
			return (0);
		i = a->x;
		a = a->next;
	}
	return (1);
}
