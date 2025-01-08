#include "push_swap.h"

// Calculate the nb of rr to do.
int	rarb(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = find_place_b(b, x);
	if (i < find_index(a, x))
		i = find_index(a, x);
	return (i);
}

// Calculate the nb of rrr to do.
int	rrarrb(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_place_b(b, x))
		i = list_size(b) - find_place_b(b, x);
	if ((i < (list_size(a) - find_index(a, x))) && find_index(a, x))
		i = list_size(a) - find_index(a, x);
	return (i);
}

int	rrarb(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_index(a, x))
		i = list_size(a) - find_index(a, x);
	i = find_place_b(b, x) + i;
	return (i);
}

int	rarrb(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_place_b(b, x))
		i = list_size(b) - find_place_b(b, x);
	i = find_index(a, x) + i;
	return (i);
}
