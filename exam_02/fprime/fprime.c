#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int x = atoi(av[1]);
		if (x < 2)
		{
			printf("\n");
			return (0);
		}
		int i = 2;
		while (x > 1)
		{
			if (x % i == 0)
			{
				printf("%i", i);
				x /= i;
				if (x > 3)
					printf("*");
			}
			else
				i++;
		}
	}
	printf("\n");
	return (0);
}
