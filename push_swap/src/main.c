#include "push_swap.h"

// This function sort the stack if there are only
// three elements in the stack.
void	sort_3(t_Node **a)
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

void	free_all(t_Node **a)
{
	t_Node	*tmp;

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

void	sort(t_Node **a)
{
	t_Node	*b;
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

int	if_dup(t_Node *a)
{
	t_Node	*tmp;

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
	t_Node	*a;

	a = NULL;
	parsing(ac, av, &a);
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
