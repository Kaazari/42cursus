#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char solution[100];
char used[100];

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	solve(int lenght, char *s, int start, char *solution, char *used)
{
	int i;
	if (start == lenght)
	{
		puts(solution);
		return ;
	}
	i = 0;
	while (i < lenght)
	{
		if (!used[i])
		{
			used[i] = 1;
			solution[start] = s[i];
			solve(lenght, s, start + 1, solution, used);
			used[i] = 0;
		}
		i++;
	}
	return ;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		char *s = av[1];
		int len = ft_strlen(s);
		solve(len, s, 0, solution, used);
	}
	return (0);
}
