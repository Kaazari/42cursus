#include "push_swap.h"

// Split nb from spaces.
void	ft_parse_args_quoted(char **av, t_Node **a)
{
	char	**tmp;

	tmp = ft_split(av[1], 32);
	list_args(tmp, a);
	ft_freestr(tmp);
	free(tmp);
	return ;
}

void	ft_parse(int ac, char **av, t_Node **a)
{
	if (ac < 2)
		ft_error();
	else if (ac == 2)
		ft_parse_args_quoted(av, a);
	else
	{
		list_args(av, a);
	}
	return ;
}

int	ft_atoi2(const char *str)
{
	int				mod;
	long long int	i;

	i = 0;
	mod = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '-')
	{
		mod = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (MAX_INT + 1);
		i = i * 10 + (*str - 48);
		str++;
	}
	if ((mod * i) > MAX_INT || (mod * i) < MIN_INT)
		return (MAX_INT + 1);
	return (mod * i);
}

// If ac == 2 (quoted).
void	sub_process(char **av, t_Node **a)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_split(av[1], 32);
	if (!tmp)
		ft_error();
	while (tmp[i])
	{
		j = ft_atoi2(tmp[i]);
		if (j > MAX_INT || j < MIN_INT)
		{
			ft_freestr(tmp);
			free(tmp);
			free_all(a);
			ft_error();
		}
		insert_end(a, j);
		i++;
	}
	ft_freestr(tmp);
	free(tmp);
	return ;
}

void	parsing(int ac, char **av, t_Node **a)
{
	int		i;
	int		j;
	int t = 0;

	i = 1;
	j = 0;
	if (ac < 2)
		ft_error();
	if (ac == 2)
		sub_process(av, a);
	else
	{
		while (i < ac)
		{
			j = ft_atoi2(av[i]);
			insert_end(a, j);
			i++;
		}
	}
	return ;
}
