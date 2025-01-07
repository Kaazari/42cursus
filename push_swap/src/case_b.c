#include "push_swap.h"

// Calculate the nb of rr to do.
int	rarb(Node *a, Node *b, int c)
{
	int	i;

	i = find_place_b(b, c);
	if (i < find_index(a, c))
		i = find_index(a, c);
	return (i);
}

// Calculate the nb of rrr to do.
int	rrarrb(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_place_b(b, c))
		i = list_size(b) - find_place_b(b, c);
	if ((i < (list_size(a) - find_index(a, c))) && find_index(a, c))
		i = list_size(a) - find_index(a, c);
	return (i);
}

int	rrarb(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_index(a, c))
		i = list_size(a) - find_index(a, c);
	i = find_place_b(b, c) + i;
	return (i);
}

int	rarrb(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_place_b(b, c))
		i = list_size(b) - find_place_b(b, c);
	i = find_index(a, c) + i;
	return (i);
}
