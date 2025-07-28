#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Allowed functions : atoi, fprintf, write

int board[20];

void	print_result(int total)
{
	int i = 0;
	while (i < total)
	{
		fprintf(stdout, "%i", board[i]);
		if (i + 1 < total)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
	return ;
}

int	is_safe(int row, int column)
{
	int i = 0;

	while (i < column)
	{
		if (board[i] - i == row - column || board[i] + i == row + column || board[i] == row)
		{
			// printf("%i, %i, %i, %i\n", board[i], i, row, column);
			return (0);
		}
		i++;
	}
	return (1);
}

void	solve(int start, int end)
{
	int i;
	if (start == end)
	{
		print_result(end);
		return ;
	}
	i = 0;
	while (i < end)
	{
		if (is_safe(i, start))
		{
			board[start] = i;
			solve(start + 1, end);
			// board[start] = 0;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = atoi(av[1]);
		solve(0, i);
	}
	return (0);
}
