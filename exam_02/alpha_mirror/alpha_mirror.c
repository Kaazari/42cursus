#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 0;
		while (av[1][i])
		{
			if (av[1][i] >= 65 && av[1][i] <= 90)
				av[1][i] = 90 - av[1][i] + 65;
			else if (av[1][i] >= 97 && av[1][i] <=122)
				av[1][i] = 122 - av[1][i] + 97;
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
