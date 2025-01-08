#include "push_swap.h"

void	ss(t_Node **a, t_Node **b)
{
	t_Node	*tmp;

	if (!*a || !((*a)->next) || !*b || !((*b)->next))
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = (*a)->next;
	(*a)->next = tmp;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = (*b)->next;
	(*b)->next = tmp;
	printf("ss\n");
}

void	rrr_utils(t_Node **b)
{
	int		i;
	t_Node	*tmp;

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
}

void	rrr(t_Node **a, t_Node **b)
{
	t_Node	*tmp;
	int		i;

	tmp = *a;
	i = 0;
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
	rrr_utils(b);
	printf("rrr\n");
}
