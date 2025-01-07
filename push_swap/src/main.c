#include "push_swap.h"

// This function sort the stack if there are only
// three elements in the stack.
void	sort_3(Node **a)
{
	if (min(*a) == (*a)->x)
	{
		rra(a);
		sa(a);
	}
	else if (max(*a) == (*a)->x)
	{
		ra(a);
		if (!sorted(*a))
			sa(a);
	}
	else
	{
		if (find_index(*a, max(*a)) == 1)
			rra(a);
		else
			sa(a);
	}
}

// This function checks if the stack is sorted.
int	sorted(Node *a)
{
	int	i;

	i = a->x;
	while (a)
	{
		if (i > a->x)
			return (0);
		i = a->x;
		a = a->next;
	}
	return (1);
}

void	free_all(Node **a)
{
	Node	*tmp;

	if (!a)
		return ;
	while (*a)
	{
		tmp = (*a)->next;
		(*a)->x = 0;
		free(*a);
		*a = tmp;
	}
}

// This function sorts the a if there are more
// than 2 elements in the a.
// And finally it makes final sort in a after
// all values pushed to b, sorted and pushed
// back to a. Because, even the a is
// sorted at the end, the minimum number have to
// at the top of the a. So, it simply brings
// the smallest number of the a to the top.
void	sort(Node **a)
{
	Node	*b;
	int		i;

	b = NULL;
	if (list_size(*a) == 2)
		sa(a);
	else
	{
		b = push_b(a);
		a = push_a(a, &b);
		i = find_index(*a, min(*a));
		if (i < list_size(*a) - i)
		{
			while ((*a)->x != min(*a))
				ra(a);
		}
		else
		{
			while ((*a)->x != min(*a))
				rra(a);
		}
	}
}

int	if_dup(Node *a)
{
	Node	*tmp;

	while (a)
	{
		tmp = a->next;
		while (tmp)
		{
			if (a->x == tmp->x)
				return (1);
			tmp = tmp->next;
		}
		a = a->next;
	}
	return (0);
}


int	main(int ac, char **av)
{
	Node	*a;

	a = parsing(ac, av);
	if (!a || if_dup(a))
	{
		free_all(&a);
		ft_error();
	}
	if (!sorted(a))
		sort(&a);
	free_all(&a);
	return (0);
}
