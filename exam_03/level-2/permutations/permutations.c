#include <unistd.h>
#include <stdlib.h>

static char	used[26];
static char	result[26];
static int	len;

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	generate(int pos)
{
	int	i;

	if (pos == len)
	{
		result[pos] = '\0';
		ft_putstr(result);
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			result[pos] = av[1][i];
			generate(pos + 1);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	len = 0;
	while (av[1][len])
		len++;

	if (len == 0)
		return (1);

	generate(0);
	return (0);
}
