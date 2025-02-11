#include <unistd.h>

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int isal(char c)
{
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (2);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 1)
	{
		int i = 1;
		int j;
		while (av[i])
		{
			j = 1;
			if (isal(av[i][0]) == 2)
				av[i][0] -= 32;
			while (av[i][j])
			{
				// if (av[i][j] && (av[i][j] == ' ' || av[i][j] == '\t') && (!isal(av[i][j])))
				// 	j++;
				if (isal(av[i][j]) == 2 && (av[i][j - 1] == ' ' || av[i][j - 1] == '\t'))
					av[i][j] -= 32;
				if (isal(av[i][j]) == 1 && (isal(av[i][j - 1]) == 2 || isal(av[i][j - 1]) == 1))
					av[i][j] += 32;
				j++;
			}
			ft_putstr(av[i]);
			write (1, "\n", 1);
			i++;
		}
	}
	if (ac < 2)
	{
		write (1, "\n", 1);
	}
}
