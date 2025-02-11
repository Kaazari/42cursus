#include <unistd.h>

int	ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	while (str[i])
	{
		res = res * 10 + str[i++] - 48;
	}
	return (res);
}

void	put_nbr(int i)
{
	if (i >= 10)
	{
		put_nbr(i / 10);
	}
	char s = i % 10 + 48;
	write(1, &s, 1);
}

int is_prime(int x)
{
	int i = 2;
	if (x <= 1)
		return (0);
	while (i * i <= x)
	{
		if (x % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i;
		int num = 0;
		i = ft_atoi(av[1]);
		while (i > 0)
		{
			if (is_prime(i))
				num += i;
			i--;
		}
		put_nbr(num);
	}
	if (ac != 2)
		put_nbr(0);
	write(1, "\n", 1);
	return (0);
}
