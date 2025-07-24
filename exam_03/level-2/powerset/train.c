#include <stdio.h>
#include <stdlib.h>

void	printer(int *subset, int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%d", subset[i]);
		i++;
		if (i < size)
			printf(" ");
	}
	printf("\n");
}

void powerset(int aim, int sum, int *set, int *subset,
			  int set_index, int subset_size, int total_elements)
{
	if (set_index == total_elements)
	{
		if (sum == aim)
			printer(subset, subset_size);  // Bonne taille !
		return ;
	}

	// Inclure set[set_index]
	subset[subset_size] = set[set_index];
	powerset(aim, sum + set[set_index], set, subset, set_index + 1, subset_size + 1, total_elements);

	// Exclure set[set_index]
	powerset(aim, sum, set, subset, set_index + 1, subset_size, total_elements);
}

int	main(int ac, char **av)
{
	if (ac > 2)
	{
		int i = 2;
		int aim = atoi(av[1]);
		int *set = calloc(ac - 1, sizeof(int));
		while (i < ac)
		{
			set[i - 2] = atoi(av[i]);
			i++;
		}
		int *subset = calloc(ac - 2, sizeof(int));
		powerset(aim, 0, set, subset, 0, 0, ac - 2);
		free(set);
		free(subset);
	}
	return (0);
}
