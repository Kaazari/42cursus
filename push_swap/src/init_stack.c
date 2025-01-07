#include "push_swap.h"

void	init_stack(Node **a, char **av, int ac)
{
	int i = 1;
	int j = 0;
	ac--;
	int *num = malloc(sizeof(int) * (ac));
	if (!num)
		return ;

	while (av[i])
	{
		num[j] = ft_atoi(av[i++]);
		j++;
	}
	j = 0;
	while (j < ac)
	{
		insert_end(a, num[j]);
		j++;
	}

	Node *n = *a;
	printf("Linked List is:\n");
	while (n != NULL)
	{
		printf("%i \n\n", n->x);
		n = n->next;
	}
	free(num);
}
