#include <unistd.h>

void ft_putnbr(int i)
{
	if (i > 9)
		ft_putnbr(i / 10);
	char c = i % 10 + 48;
	write(1, &c, 1);
}

int ft_atoi(char *s)
{
	int res = 0;
	int i = 0;
	while (s[i]) // && s[i] >= 48 && s[i <= 57])
	{
		res *= 10;
		res += s[i] - 48;
		i++;
	}
	return (res);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 1;
		int x = ft_atoi(av[1]);
		while (i <= 9)
		{
			ft_putnbr(i);
			write(1, " x ", 3);
			ft_putnbr(x);
			write(1, " = ", 3);
			ft_putnbr(i * x);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		write(1, "\n", 1);
	}
}
