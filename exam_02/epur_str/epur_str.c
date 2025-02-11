#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 0;
		int len = 0;
		int state = 0;
		while (av[1][len])
			len++;
		while (av[1][i] == 32 || av[1][i] == 9)
			i++;
		int end = len;
		while (end != 0 && (av[1][end] == 32 || av[1][end] == 9))
		{
			end--;
		}
		while (av[1][i])
		{
			while (av[1][i] == 32 || av[1][i] == 9)
			{
				state = 1;
				i++;
			}
			if (state == 1)
			{
				state = 0;
				if (i < end)
					write(1, " ", 1);
			}
			if (i < len)
				write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
