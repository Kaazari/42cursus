#include "push_swap.h"

void	ft_error(void)
{
	write (2, "Error\n", 6);
	exit(1);
}

//chec if the chracter is negative
int	sign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

//check if the character is digit
int	digit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}

//check if character is space character
int	space(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

//function to check if given arguments is valid
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
				if (!digit(argv[i][j]))
					return (false);
			}
			else if (digit(argv[i][j]))
			{
				j++;
				if (argv[i][j] == '\0')
					break ;
				if (!digit(argv[i][j]) && !space(argv[i][j]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

// Creates new stack node with given number.
Node	*ft_stack_new(int content)
{
	Node	*new;

	new = malloc(sizeof (Node));
	if (!new)
		ft_error();
	new->x = content;
	new->next = NULL;
	return (new);
}

void	ft_add_back(Node **stack, Node *stack_new)
{
	if (!stack)
		return ;
	if (!*stack)
		*stack = stack_new;
	else
		(last_node(*stack))->next = stack_new;
}

// While arguments are valid, we start to add them
// into stack here one by one with while loop.
// Atoi takes the number and turn it into an integer
// value where we can make math operations.
// With stack new we create a new node for the current
// argument without linking it to list.
// We make linking stage in ft_add_back call.
void	list_args(char **av, Node **a)
{
	long	i;

	i = 1;
	while (av[i] != NULL)
	{
		ft_add_back(a, ft_stack_new(ft_atoi(av[i])));
		i++;
	}
}

// This function free the string which is
// the integer values in between quotes.
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

// Function to parse the arguments from the quoted string
// and send them to list_args function to add them into list.
// With ft_split we split numbers from spaces.
Node	*ft_parse_args_quoted(char **av)
{
	Node	*a;
	char	**tmp;
	int		i;

	a = NULL;
	i = 0;
	tmp = ft_split(av[1], 32);
	list_args(tmp, &a);
	ft_freestr(tmp);
	free(tmp);
	return (a);
}

// This function does three things.
// 1. It checks if the number of input is less than 2.
// 2. It checks if the number of input is equal to 2.
//    If it is, it means it is a quoted string.
// 3. It checks if the number of input is greater than 2.
//     If it is, it lists the arguements.
Node	*ft_parse(int ac, char **av)
{
	Node	*a;
	int		i;

	i = 1;
	a = NULL;
	if (ac < 2)
		ft_error();
	else if (ac == 2)
		a = ft_parse_args_quoted(av);
	else
	{
		list_args(av, &a);
	}
	return (a);
}
//function which checks the character if it is alphanumerical
int	ft_isalpha(int c)
{
	if ((c >= 58 && c <= 126) || (c >= 33 && c <= 42)
		|| (c == 44) || (c == 46) || (c == 47))
		return (1);
	return (0);
}

//Here arguments are send to make ASCII check
//regarding the alphanumeric values
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

//With this function it is checked
//whether arguments include alfanumeric or not
int	check_args(char **av)
{
	alpha_check(av);
	if (!check_error(av, 1, 0))
		return (false);
	return (true);
}

// This function does three things.
// 1. It checks if the number of input is less than 2.
// 2. It checks if the number of input is equal to 2.
//    If it is, it means it is a quoted string.
// 3. It checks if the number of input is greater than 2.
//     If it is, it lists the arguements.
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
			ft_error();
		i = i * 10 + (*str - 48);
		str++;
	}
	if ((mod * i) > 2147483647 || (mod * i) < -2147483648)
		ft_error();
	return (mod * i);
}

// This function works and sorts the stacks
// in case of they are passed in between quotation
// marks. In this scenario, this function takes the
// string, and splits the numbers in order to create
// seperated integer number.
Node	*ft_sub_process(char **av)
{
	Node	*a;
	char	**tmp;
	int		i;
	int		j;

	a = NULL;
	i = 0;
	tmp = ft_split(av[1], 32);
	while (tmp[i])
	{
		j = ft_atoi2(tmp[i]);
		ft_add_back(&a, ft_stack_new(j));
		i++;
	}
	ft_freestr(tmp);
	free(tmp);
	return (a);
}

// This function does three things.
// 1. It checks if the number of input is less than 2.
// 2. It checks if the number of input is equal to 2.
//    If it is, it means it is a quoted string. Call
//	  another function. <ft_sub_process>
// 3. It checks if the number of input is greater than 2.
//     If it is, it lists the arguements.
Node	*parsing(int ac, char **av)
{
	Node	*a;
	int		i;
	int		j;

	i = 1;
	a = NULL;
	if (ac < 2)
		ft_error();
	if (ac == 2)
		a = ft_sub_process(av);
	else
	{
		while (i < ac)
		{
			j = ft_atoi2(av[i]);
			ft_add_back(&a, ft_stack_new(j));
			i++;
		}
	}
	return (a);
}
