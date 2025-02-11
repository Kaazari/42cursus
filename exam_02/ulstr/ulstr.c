#include <unistd.h>

void	ulstr(char *s)
{
	int	i = 0;
	if (!s)
	{
		write(1, "\n", 1);
		return;
	}
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		else if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
		// c = s[i];
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	ulstr(av[1]);
	return (0);
}
