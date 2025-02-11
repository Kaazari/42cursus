#include <unistd.h>

int	ft_len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check(char s, char *str, int index)
{
	int i = 0;
	while (i < index)
	{
		if (s == str[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	while (s1[i])
	{
		if (check(s1[i], s1, i) == 1)
			write(1, &s1[i], 1);
		i++;
		j = i;
	}
	i = 0;
	while (s2[i])
	{
		if (check(s2[i], s2, i) == 1)
		{
			if (check(s2[i], s1, j) == 1)
				write(1, &s2[i], 1);
		}
		i++;
	}
	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	ft_union(av[1], av[2]);
	return (0);
}
