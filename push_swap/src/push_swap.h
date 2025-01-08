#ifndef PUSH_SWAP
# define PUSH_SWAP

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"

// t_Node **root when modifying the loop itself, t_Node *root for info only

typedef struct t_Node
{
	int				x;
	struct t_Node	*next;
}	t_Node;

// Parsing
void	parsing(int ac, char **av, t_Node **a);
void	sub_process(char **av, t_Node **a);
int		ft_atoi2(const char *str);
void	ft_parse_args_quoted(char **av, t_Node **a);
void	ft_parse(int ac, char **av, t_Node **a);
void	alpha_check(char **av);
int		check_args(char **av);
void	list_args(char **av, t_Node **a);
int		sign(int c);

// t_Node management
void	insert_after(t_Node *node, int value);
void	insert_beginning(t_Node **root, int value);
void	insert_end(t_Node **root, int value);
void	insert_sorted(t_Node **root, int value);
void	deallocate(t_Node **root);
void	remove_node(t_Node **root, int value);
void	reverse(t_Node **root);
int		has_loops(t_Node *root);
int		count(t_Node *root);
t_Node	*last_node(t_Node *a);

// Actions
void	sa(t_Node **a);
void	sb(t_Node **b);
void	ss(t_Node **a, t_Node **b);
void	pb(t_Node **a, t_Node **b);
void	pa(t_Node **a, t_Node **b);
void	ra(t_Node **a);
void	rb(t_Node **b);
void	rr(t_Node **a, t_Node **b);
void	rra(t_Node **a);
void	rrr(t_Node **a, t_Node **b);
void	rrb(t_Node **b);

// Sort utils
t_Node	**push_a(t_Node **a, t_Node **b);
t_Node	*push_b(t_Node **a);
int		find_index(t_Node *a, int x);
int		list_size(t_Node *a);
int		sorted(t_Node *a);
int		max(t_Node *a);
int		min(t_Node *a);
void	sort_3(t_Node **a);
void	print_list(t_Node *a);

// Cases
int		rarb(t_Node *a, t_Node *b, int c);
int		rrarrb(t_Node *a, t_Node *b, int c);
int		rrarb(t_Node *a, t_Node *b, int c);
int		rarrb(t_Node *a, t_Node *b, int c);
int		rrarb_a(t_Node *a, t_Node *b, int c);
int		rarrb_a(t_Node *a, t_Node *b, int c);
int		rrarrb_a(t_Node *a, t_Node *b, int c);
int		rarb_a(t_Node *a, t_Node *b, int c);
int		apply_rarb(t_Node **a, t_Node **b, int c, char s);
int		apply_rrarrb(t_Node **a, t_Node **b, int c, char s);
int		apply_rrarrb(t_Node **a, t_Node **b, int c, char s);
int		apply_rrarb(t_Node **a, t_Node **b, int c, char s);
int		apply_rarrb(t_Node **a, t_Node **b, int c, char s);
int		best_rotate_ab(t_Node *a, t_Node *b);
int		best_rotate_ba(t_Node *a, t_Node *b);
int		find_place_a(t_Node *a, int x);
int		find_place_b(t_Node *b, int x);

// Errors & sort check
int		if_dup(t_Node *a);
void	ft_error(void);
void	ft_freestr(char **lst);
int		check_error(char **argv, int i, int j);

#endif
