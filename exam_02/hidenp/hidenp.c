#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while(av[1][i])
		{
			while(av[2][j])
			{
				if (av[1][i] == av[2][j])
				{
					k = 1;
					break ;
				}
				k = 0;
				j++;
			}
			if (k == 0)
			{
				write(1, "0\n", 2);
				return (1);
			}
			i++;
		}
		write(1, "1", 1);
	}
	write(1, "\n", 1);
	return (0);
}
