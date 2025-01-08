#include "push_swap.h"

void	rb(t_Node **b)
{
	t_Node	*tmp;

	tmp = *b;
	*b = last_node(*b);
	(*b)->next = tmp;
	*b = tmp->next;
	tmp->next = NULL;
	printf("rb\n");
}

void	rr(t_Node **a, t_Node **b)
{
	t_Node	*tmp;

	tmp = *a;
	*a = last_node(*a);
	(*a)->next = tmp;
	*a = tmp->next;
	tmp->next = NULL;
	tmp = *b;
	*b = last_node(*b);
	(*b)->next = tmp;
	*b = tmp->next;
	tmp->next = NULL;
	printf("rr\n");
}

void	rra(t_Node **a)
{
	t_Node	*tmp;
	int		i;

	i = 0;
	tmp = *a;
	while ((*a)->next)
	{
		*a = (*a)->next;
		i++;
	}
	(*a)->next = tmp;
	while (i > 1)
	{
		tmp = tmp->next;
		i--;
	}
	tmp->next = NULL;
	printf("rra\n");
}

void	rrb(t_Node **b)
{
	t_Node	*tmp;
	int		i;

	tmp = *b;
	i = 0;
	while ((*b)->next)
	{
		*b = (*b)->next;
		i++;
	}
	(*b)->next = tmp;
	while (i > 1)
	{
		tmp = tmp->next;
		i--;
	}
	tmp->next = NULL;
	printf("rrb\n");
}
