#include "push_swap.h"

// Check alpha w/ ascii.
void	alpha_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while ((av[i][j]) != '\0')
		{
			if (ft_isalpha(av[i][j]))
				ft_error();
			j++;
		}
		i++;
	}
}

// Check alphanum.
int	check_args(char **av)
{
	alpha_check(av);
	if (!check_error(av, 1, 0))
		return (false);
	return (true);
}

void	ft_freestr(char **lst)
{
	char	*n1;

	if (!lst)
		return ;
	while (*lst)
	{
		n1 = *lst;
		lst++;
		free(n1);
	}
	*lst = NULL;
}

// Add av in the stack.
void	list_args(char **av, t_Node **a)
{
	long	i;

	i = 1;
	while (av[i] != NULL)
	{
		insert_end(a, ft_atoi(av[i]));
		i++;
	}
}

// Chesk if av is valid.
int	check_error(char **argv, int i, int j)
{
	while (argv[i])
	{
		j = 0;
		while ((argv[i][j] != '\0'))
		{
			if (sign(argv[i][j]))
			{
				j++;
				if (!ft_isdigit(argv[i][j]))
					return (false);
			}
			else if (ft_isdigit(argv[i][j]))
			{
				j++;
				if (argv[i][j] == '\0')
					break ;
				if (!ft_isdigit(argv[i][j]) && !ft_isspace(argv[i][j]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
