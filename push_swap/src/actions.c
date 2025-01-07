#include "push_swap.h"

void	sa(Node **a)
{
	if (!a)
		return ;
	Node *tmp = *a;
	*a = (*a)->next;
	tmp->next = (*a)->next;
	(*a)->next = tmp;
	printf("sa\n");
}

void	sb(Node **b)
{
	if (!b)
		return ;
	Node *tmp = *b;
	*b = (*b)->next;
	tmp->next = (*b)->next;
	(*b)->next = tmp;
	printf("sb\n");
}

// void	ss(Node **a, Node **b)
// {
// 	sa(a);
// 	sa(b);
// }

void	pa(Node **a, Node **b)
{
	if (!*b)
		return ;
	Node *tmp = *a;
	*a = *b;
	*b = (*b)->next;
	(*a)->next = tmp;
	printf("pa\n");
}

void	pb(Node **a, Node **b)
{
	if (!*a)
		return ;
	Node *tmp = *b;
	*b = *a;
	*a = (*a)->next;
	(*b)->next = tmp;
	printf("pb\n");
}

void	ra(Node **a)
{
	Node *tmp = *a;
	*a = last_node(*a);
	(*a)->next = tmp;
	*a = tmp->next;
	tmp->next = NULL;
	printf("ra\n");
}
