#include "push_swap.h"

// The application of each cases.

int	apply_rarb(Node **a, Node **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != c && find_place_b(*b, c) > 0)
			rr(a, b);
		while ((*a)->x != c)
			ra(a);
		while (find_place_b(*b, c) > 0)
			rb(b);
		pb(a, b);
	}
	else
	{
		while ((*b)->x != c && find_place_a(*a, c) > 0)
			rr(a, b);
		while ((*b)->x != c)
			rb(b);
		while (find_place_a(*a, c) > 0)
			ra(a);
		pa(a, b);
	}
	return (-1);
}

int	apply_rrarrb(Node **a, Node **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != c && find_place_b(*b, c) > 0)
			rrr(a, b);
		while ((*a)->x != c)
			rra(a);
		while (find_place_b(*b, c) > 0)
			rrb(b);
		pb(a, b);
	}
	else
	{
		while ((*b)->x != c && find_place_a(*a, c) > 0)
			rrr(a, b);
		while ((*b)->x != c)
			rrb(b);
		while (find_place_a(*a, c) > 0)
			rra(a);
		pa(a, b);
	}
	return (-1);
}

int	apply_rrarb(Node **a, Node **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != c)
			rra(a);
		while (find_place_b(*b, c) > 0)
			rb(b);
		pb(a, b);
	}
	else
	{
		while (find_place_a(*a, c) > 0)
			rra(a);
		while ((*b)->x != c)
			rb(b);
		pa(a, b);
	}
	return (-1);
}

int	apply_rarrb(Node **a, Node **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != c)
			ra(a);
		while (find_place_b(*b, c) > 0)
			rrb(b);
		pb(a, b);
	}
	else
	{
		while (find_place_a(*a, c) > 0)
			ra(a);
		while ((*b)->x != c)
			rrb(b);
		pa(a, b);
	}
	return (-1);
}
