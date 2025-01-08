#include "push_swap.h"

int	find_index(t_Node *a, int num)
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

int	best_rotate_ba(t_Node *a, t_Node *b)
{
	int		i;
	t_Node	*tmp;

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

int	best_rotate_ab(t_Node *a, t_Node *b)
{
	int		i;
	t_Node	*tmp;

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

t_Node	**push_a(t_Node **a, t_Node **b)
{
	int		i;
	t_Node	*tmp;

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
