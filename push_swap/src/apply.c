#include "push_swap.h"

// The application of each cases.

int	apply_rarb(t_Node **a, t_Node **b, int x, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != x && find_place_b(*b, x) > 0)
			rr(a, b);
		while ((*a)->x != x)
			ra(a);
		while (find_place_b(*b, x) > 0)
			rb(b);
		pb(a, b);
	}
	else
	{
		while ((*b)->x != x && find_place_a(*a, x) > 0)
			rr(a, b);
		while ((*b)->x != x)
			rb(b);
		while (find_place_a(*a, x) > 0)
			ra(a);
		pa(a, b);
	}
	return (-1);
}

int	apply_rrarrb(t_Node **a, t_Node **b, int x, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != x && find_place_b(*b, x) > 0)
			rrr(a, b);
		while ((*a)->x != x)
			rra(a);
		while (find_place_b(*b, x) > 0)
			rrb(b);
		pb(a, b);
	}
	else
	{
		while ((*b)->x != x && find_place_a(*a, x) > 0)
			rrr(a, b);
		while ((*b)->x != x)
			rrb(b);
		while (find_place_a(*a, x) > 0)
			rra(a);
		pa(a, b);
	}
	return (-1);
}

int	apply_rrarb(t_Node **a, t_Node **b, int x, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != x)
			rra(a);
		while (find_place_b(*b, x) > 0)
			rb(b);
		pb(a, b);
	}
	else
	{
		while (find_place_a(*a, x) > 0)
			rra(a);
		while ((*b)->x != x)
			rb(b);
		pa(a, b);
	}
	return (-1);
}

int	apply_rarrb(t_Node **a, t_Node **b, int x, char s)
{
	if (s == 'a')
	{
		while ((*a)->x != x)
			ra(a);
		while (find_place_b(*b, x) > 0)
			rrb(b);
		pb(a, b);
	}
	else
	{
		while (find_place_a(*a, x) > 0)
			ra(a);
		while ((*b)->x != x)
			rrb(b);
		pa(a, b);
	}
	return (-1);
}
