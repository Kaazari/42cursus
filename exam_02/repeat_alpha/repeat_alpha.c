#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 0;
		int rep = 0;
		while(av[1][i])
		{
			rep = 0;
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
				rep = av[1][i] - 97;
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
				rep = av[1][i] - 65;
			while (rep >= 0)
			{
				write(1, &av[1][i], 1);
				rep--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
