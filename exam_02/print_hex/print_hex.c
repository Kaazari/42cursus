#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_atoi(char* num)
{
	int x = 0;
	int i = 0;
	while (num[i])
	{
		x += num[i] - 48;
		if (num[i + 1] != '\0')
			x *= 10;
		i++;
	}
	return (x);
}

void	putnbr_base(int num, char *base)
{
	if (num >= 16)
	{
		putnbr_base(num / 16, base);
		write(1, &base[num % 16], 1);
	}
	else
		write(1, &base[num % 16], 1);
	return ;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		char *base = "0123456789abcdef";
		int num = ft_atoi(av[1]);
		putnbr_base(num, base);
	}
	write(1, "\n", 1);
	return (0);
}
