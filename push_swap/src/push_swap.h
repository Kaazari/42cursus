#ifndef PUSH_SWAP
# define PUSH_SWAP

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"



// Node **root when modifying the loop itself, Node *root for info only



typedef struct	Node {
	int				x;			// the value stored in the node
	struct Node		*next;
}	Node;


// Parsing


void	ft_error(void);
int		sign(int c);
int		digit(int c);
int		space(int c);
int		check_error(char **argv, int i, int j);
Node	*ft_stack_new(int content);
void	ft_add_back(Node **stack, Node *stack_new);
void	list_args(char **av, Node **a);
void	ft_freestr(char **lst);
Node	*ft_parse_args_quoted(char **av);
Node	*ft_parse(int ac, char **av);
int		ft_isalpha(int c);
void	alpha_check(char **av);
int		check_args(char **av);
int		ft_atoi2(const char *str);
Node	*ft_sub_process(char **av);

// Node management


void	insert_after(Node *node, int value);
void	insert_beginning(Node **root, int value);
void	insert_end(Node **root, int value);
void	insert_sorted(Node **root, int value);
void	deallocate(Node **root);
void	remove_node(Node **root, int value);
void	reverse(Node **root);
int		has_loops(Node *root);
int		count(Node *root);
Node	*last_node(Node *a);

// Stack init && parsing


void	init_stack(Node **a, char **av, int ac);
// Node	*ft_process(int ac, char **av);

// Actions


void	sa(Node **a);
void	sb(Node **b);
void	ss(Node **a, Node **b);
void	pb(Node **a, Node **b);
void	pa(Node **a, Node **b);
void	ra(Node **a);
void	rb(Node **b);
void	rr(Node **a, Node **b);
void	rra(Node **a);
void	rrr(Node **a, Node **b);
void	rrb(Node **b);

// Sort utils


Node	**push_a(Node **a, Node **b);
Node	*push_b(Node **a);
int		find_index(Node *a, int x);
int		list_size(Node *a);
int 	sorted(Node *a);
int		max(Node *a);
int 	min(Node *a);
void	sort_3(Node **a);
void	print_list(Node *a);

// Cases


int		rarb(Node *a, Node *b, int c);
int		rrarrb(Node *a, Node *b, int c);
int		rrarb(Node *a, Node *b, int c);
int		rarrb(Node *a, Node *b, int c);
int		rrarb_a(Node *a, Node *b, int c);
int		rarrb_a(Node *a, Node *b, int c);
int		rrarrb_a(Node *a, Node *b, int c);
int		rarb_a(Node *a, Node *b, int c);
int		apply_rarb(Node **a, Node **b, int c, char s);
int		apply_rrarrb(Node **a, Node **b, int c, char s);
int		apply_rrarrb(Node **a, Node **b, int c, char s);
int		apply_rrarb(Node **a, Node **b, int c, char s);
int		apply_rarrb(Node **a, Node **b, int c, char s);
int		best_rotate_ab(Node *a, Node *b);
int		best_rotate_ba(Node *a, Node *b);
int		find_place_a(Node *a, int x);
int		find_place_b(Node *b, int x);


// Errors & sort check

int		if_dup(Node *a);
void	ft_error(void);
void	ft_freestr(char **lst);
Node	*parsing(int ac, char **av);


#endif
