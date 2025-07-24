#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	sort(char *s)
{
	int i = 0;
	int j;
	char	tmp;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[i] > s[j])
			{
				tmp = s[j];
				s[j] = s[i];
				s[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	permute(int start, char *s, int len, char *solution, int *used)
{
	int i;
	if (start == len)
	{
		puts(solution);
	}
	i = 0;
	while (s[i])
	{
		if (!used[i])
		{
			solution[start] = s[i];
			used[i] = 1;
			permute(start + 1, s, len, solution, used);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		char *s = av[1];
		int i = 0;
		while (s[i])
			i++;
		char *solution = malloc(i + 1);
		int *used = calloc(i, sizeof(int));
		solution[i] = '\0';
		sort(s);
		permute(0, s, i, solution, used);
		free(solution);
		free(used);
	}
	return (0);
}
