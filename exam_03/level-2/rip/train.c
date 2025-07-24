#include <stdio.h>

void	calculate_removals(char *s, int *excess_open, int *excess_close)
{
	int balance = 0;
	int close_excess = 0;
	int i = 0;

	while (s[i])
	{
		if (s[i] == '(')
		{
			balance++;
		}
		else if (s[i] == ')')
		{
			if (balance > 0)
			{
				balance--;  // Apparie avec un ( précédent
			}
			else
			{
				close_excess++;  // ) sans ( correspondante
			}
		}
		i++;
	}

	*excess_open = balance;	  // ( non fermées
	*excess_close = close_excess; // ) sans (
	return balance + close_excess;
}

void solve(char *s, int pos, int open_to_remove, int close_to_remove, int balance)
{
	// Condition d'arrêt
	if (!s[pos])
	{
		if (open_to_remove == 0 && close_to_remove == 0 && balance == 0)
			puts(s);  // Affiche la solution
		return;
	}

	// Pour '('
	if (s[pos] == '(') {
		// Choix 1: supprimer
		if (open_to_remove > 0) {
			char backup = s[pos];
			s[pos] = ' ';
			solve(s, pos + 1, open_to_remove - 1, close_to_remove, balance);
			s[pos] = backup;
		}
		// Choix 2: garder
		solve(s, pos + 1, open_to_remove, close_to_remove, balance + 1);
	}

	// Pour ')'
	if (s[pos] == ')') {
		// Choix 1: supprimer
		if (close_to_remove > 0) {
			char backup = s[pos];
			s[pos] = ' ';
			solve(s, pos + 1, open_to_remove, close_to_remove - 1, balance);
			s[pos] = backup;
		}
		// Choix 2: garder (si possible)
		if (balance > 0) {
			solve(s, pos + 1, open_to_remove, close_to_remove, balance - 1);
		}
}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		char *str = av[1];
		char *res = str;
		int excess_open;
		int excess_close;
		int i = calculate_removals(str, excess_open, excess_close);
		solve(str, 0, excess_open, excess_close, 0);
	}
}
