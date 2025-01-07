#include "push_swap.h"

// This function finds the correct place of the number in b.
// In other words, it check what index number num will get
// after it is being pushed to the b.
int	find_place_b(Node *b, int num)
{
	int		i;
	Node	*tmp;

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

// This function finds the correct place of the number in a.
// In other words, it check what index number num will get
// after it is being pushed to the a.
int	find_place_a(Node *a, int num)
{
	int		i;
	Node	*tmp;

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

// This function sort and push stacks until 3 members left behind.
void	sort_to_3(Node **a, Node **b)
{
	int		i;
	Node	*tmp;

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

// This function one by one pushes all the elements
// in a to the b, until only three elements
// are left in a. While pushing, it makes sure if
// the b is sorted. When three elements are left,
// it calls the ft_sort_three function to sort left over
// elements in a.
Node	*push_b(Node **a)
{
	Node	*b;

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
