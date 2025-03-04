#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 2;
		int num = atoi(av[1]);
		if (num < 2)
		{
			printf("\n");
			return (0);
		}
		while (num > 1)
		{
			if (num % i == 0)
			{
				printf("%i", i);
				num /= i;
				if (num > 3)
					printf("*");
			}
			else
				i++;
		}
	}
	printf("\n");
	return (0);
}
