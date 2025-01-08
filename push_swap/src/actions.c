#include "push_swap.h"

void	sa(t_Node **a)
{
	t_Node	*tmp;

	if (!a)
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = (*a)->next;
	(*a)->next = tmp;
	printf("sa\n");
}

void	sb(t_Node **b)
{
	t_Node	*tmp;

	if (!b)
		return ;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = (*b)->next;
	(*b)->next = tmp;
	printf("sb\n");
}

void	pa(t_Node **a, t_Node **b)
{
	t_Node	*tmp;

	if (!*b)
		return ;
	tmp = *a;
	*a = *b;
	*b = (*b)->next;
	(*a)->next = tmp;
	printf("pa\n");
}

void	pb(t_Node **a, t_Node **b)
{
	t_Node	*tmp;

	if (!*a)
		return ;
	tmp = *b;
	*b = *a;
	*a = (*a)->next;
	(*b)->next = tmp;
	printf("pb\n");
}

void	ra(t_Node **a)
{
	t_Node	*tmp;

	tmp = *a;
	*a = last_node(*a);
	(*a)->next = tmp;
	*a = tmp->next;
	tmp->next = NULL;
	printf("ra\n");
}
