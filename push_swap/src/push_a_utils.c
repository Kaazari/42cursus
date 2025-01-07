#include "push_swap.h"

// This function checks the index of a number
// 	 in the stack.
int	find_index(Node *a, int num)
{
	int		i;

	i = 0;
	while (a->x != num)
	{
		i++;
		a = a->next;
	}
	return (i);
}

// This function calculate and decides which rotation
// combination is best to use to sort the stack. Of
// course, after rotation there is always one push
// operation is left to do which i embeded to code.
// Function is used during push from B to A.
int	best_rotate_ba(Node *a, Node *b)
{
	int		i;
	Node	*tmp;

	tmp = b;
	i = rrarrb_a(a, b, b->x);
	while (tmp)
	{
		if (i > rarb_a(a, b, tmp->x))
			i = rarb_a(a, b, tmp->x);
		if (i > rrarrb_a(a, b, tmp->x))
			i = rrarrb_a(a, b, tmp->x);
		if (i > rarrb_a(a, b, tmp->x))
			i = rarrb_a(a, b, tmp->x);
		if (i > rrarb_a(a, b, tmp->x))
			i = rrarb_a(a, b, tmp->x);
		tmp = tmp->next;
	}
	return (i);
}

// This function calculate and decides which rotation
// combination is best to use to sort the stack. Of
// course, after rotation there is always one push
// operation is left to do which i embeded to code.
// Function is used during push from A to B.
int	best_rotate_ab(Node *a, Node *b)
{
	int		i;
	Node	*tmp;

	tmp = a;
	i = rrarrb(a, b, a->x);
	while (tmp)
	{
		if (i > rarb(a, b, tmp->x))
			i = rarb(a, b, tmp->x);
		if (i > rrarrb(a, b, tmp->x))
			i = rrarrb(a, b, tmp->x);
		if (i > rarrb(a, b, tmp->x))
			i = rarrb(a, b, tmp->x);
		if (i > rrarb(a, b, tmp->x))
			i = rrarb(a, b, tmp->x);
		tmp = tmp->next;
	}
	return (i);
}

// This function is pushing back the elements from b
// to a until b is empty.
Node	**push_a(Node **a, Node **b)
{
	int		i;
	Node	*tmp;

	while (*b)
	{
		tmp = *b;
		i = best_rotate_ba(*a, *b);
		while (i >= 0)
		{
			if (i == rarb_a(*a, *b, tmp->x))
				i = apply_rarb(a, b, tmp->x, 'b');
			else if (i == rarrb_a(*a, *b, tmp->x))
				i = apply_rarrb(a, b, tmp->x, 'b');
			else if (i == rrarrb_a(*a, *b, tmp->x))
				i = apply_rrarrb(a, b, tmp->x, 'b');
			else if (i == rrarb_a(*a, *b, tmp->x))
				i = apply_rrarb(a, b, tmp->x, 'b');
			else
				tmp = tmp->next;
		}
	}
	return (a);
}
