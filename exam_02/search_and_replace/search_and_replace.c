#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 4)
	{
		int i = 0;
		while (av[2][i])
		{
			if (i >= 2)
			{
				write(1, "\n", 1);
				return (0);
			}
			i++;
		}
		i = 0;
		while (av[3][i])
		{
			if (i >= 2)
			{
				write(1, "\n", 1);
				return (0);
			}
			i++;
		}
		i = 0;
		while (av[1][i])
		{
			if (av[2][0] == av[1][i])
				write(1, &av[3][0], 1);
			else
				write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
