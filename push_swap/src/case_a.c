#include "push_swap.h"

// Calculate the nb of rota needed for each ways.

int	rarb_a(Node *a, Node *b, int c)
{
	int	i;

	i = find_place_a(a, c);
	if (i < find_index(b, c))
		i = find_index(b, c);
	return (i);
}

int	rrarrb_a(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_place_a(a, c))
		i = list_size(a) - find_place_a(a, c);
	if ((i < (list_size(b) - find_index(b, c))) && find_index(b, c))
		i = list_size(b) - find_index(b, c);
	return (i);
}

int	rarrb_a(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_index(b, c))
		i = list_size(b) - find_index(b, c);
	i = find_place_a(a, c) + i;
	return (i);
}

int	rrarb_a(Node *a, Node *b, int c)
{
	int	i;

	i = 0;
	if (find_place_a(a, c))
		i = list_size(a) - find_place_a(a, c);
	i = find_index(b, c) + i;
	return (i);
}
