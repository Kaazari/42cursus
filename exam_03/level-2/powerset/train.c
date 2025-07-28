#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Allowed functions : atoi, printf, malloc, calloc, realloc, free.

int subset[20];

void	print_result(int *subset, int len)
{
	int i = 0;
	while (i < len)
	{
		printf("%d", subset[i]);
		if (i + 1 < len)
			printf(" ");
		i++;
	}
	printf("\n");
	return ;
}

void	solve(int aim, int start, int *set, int *subset, int result, int total, int index)
{
	if (start >= total)
	{
		if (result == aim)
			print_result(subset, index);
		return ;
	}

	solve(aim, start + 1, set, subset, result, total, index);
	subset[index] = set[start];
	solve(aim, start + 1, set, subset, result + subset[index], total, index + 1);
	return ;
}

int	main(int ac, char **av)
{
	if (ac > 2)
	{
		int i = 2;
		int ref = atoi(av[1]);
		int set[20];
		while (av[i])
		{
			set[i - 2] = atoi(av[i]);
			i++;
		}
		solve(ref, 0, set, subset, 0, i - 2, 0);
	}
	printf("\n");
	return (0);
}
