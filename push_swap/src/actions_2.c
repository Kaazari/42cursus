#include "push_swap.h"

void	rb(Node **b)
{
	Node *tmp = *b;
	*b = last_node(*b);
	(*b)->next = tmp;
	*b = tmp->next;
	tmp->next = NULL;
	printf("rb\n");
}

void	rr(Node **a, Node **b)
{
	Node *tmp = *a;
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

void	rra(Node **a)
{
	Node *tmp = *a;
	int i = 0;
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

void	rrb(Node **b)
{
	Node *tmp = *b;
	int i = 0;
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

void	rrr(Node **a, Node **b)
{
	Node *tmp = *a;
	int i = 0;
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
	printf("rrr\n");
}
