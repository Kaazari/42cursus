#include "push_swap.h"

// Calculate the nb of rota needed for each ways.

int	rarb_a(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = find_place_a(a, x);
	if (i < find_index(b, x))
		i = find_index(b, x);
	return (i);
}

int	rrarrb_a(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_place_a(a, x))
		i = list_size(a) - find_place_a(a, x);
	if ((i < (list_size(b) - find_index(b, x))) && find_index(b, x))
		i = list_size(b) - find_index(b, x);
	return (i);
}

int	rarrb_a(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_index(b, x))
		i = list_size(b) - find_index(b, x);
	i = find_place_a(a, x) + i;
	return (i);
}

int	rrarb_a(t_Node *a, t_Node *b, int x)
{
	int	i;

	i = 0;
	if (find_place_a(a, x))
		i = list_size(a) - find_place_a(a, x);
	i = find_index(b, x) + i;
	return (i);
}
