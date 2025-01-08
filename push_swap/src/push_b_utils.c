#include "push_swap.h"

// The index from a to b.
int	find_place_b(t_Node *b, int num)
{
	int		i;
	t_Node	*tmp;

	i = 1;
	if (num > b->x && num < last_node(b)->x)
		i = 0;
	else if (num > max(b) || num < min(b))
		i = find_index(b, max(b));
	else
	{
		tmp = b->next;
		while (b->x < num || tmp->x > num)
		{
			b = b->next;
			tmp = b->next;
			i++;
		}
	}
	return (i);
}

// The index number from b to a.
int	find_place_a(t_Node *a, int num)
{
	int		i;
	t_Node	*tmp;

	i = 1;
	if (num < a->x && num > last_node(a)->x)
		i = 0;
	else if (num > max(a) || num < min(a))
		i = find_index(a, min(a));
	else
	{
		tmp = a->next;
		while (a->x > num || tmp->x < num)
		{
			a = a->next;
			tmp = a->next;
			i++;
		}
	}
	return (i);
}

// This function sort and push stacks until 3 int left.
void	sort_to_3(t_Node **a, t_Node **b)
{
	int		i;
	t_Node	*tmp;

	while (list_size(*a) > 3 && !sorted(*a))
	{
		tmp = *a;
		i = best_rotate_ab(*a, *b);
		while (i >= 0)
		{
			if (i == rarb(*a, *b, tmp->x))
				i = apply_rarb(a, b, tmp->x, 'a');
			else if (i == rrarrb(*a, *b, tmp->x))
				i = apply_rrarrb(a, b, tmp->x, 'a');
			else if (i == rarrb(*a, *b, tmp->x))
				i = apply_rarrb(a, b, tmp->x, 'a');
			else if (i == rrarb(*a, *b, tmp->x))
				i = apply_rrarb(a, b, tmp->x, 'a');
			else
				tmp = tmp->next;
		}
	}
}

t_Node	*push_b(t_Node **a)
{
	t_Node	*b;

	b = NULL;
	if (list_size(*a) > 3 && !sorted(*a))
		pb(a, &b);
	if (list_size(*a) > 3 && !sorted(*a))
		pb(a, &b);
	if (list_size(*a) > 3 && !sorted(*a))
		sort_to_3(a, &b);
	if (!sorted(*a))
		sort_3(a);
	return (b);
}
