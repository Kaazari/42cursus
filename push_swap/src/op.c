#include "push_swap.h"

void	insert_after(Node *node, int value)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
		exit(1);
	new_node->x = value;
	new_node->next = node->next;
	node->next = new_node;
}

void	insert_beginning(Node **root, int value)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
		exit(1);

	new_node->x = value;
	new_node->next = *root;

	*root = new_node;
}

void	insert_end(Node **root, int value)		// add a new node at the end of the linked list
{
	Node *new_node = malloc(sizeof(Node));
	if (!new_node)
		exit(1);
	new_node->next = NULL;
	new_node->x = value;

	if (*root == NULL)
	{
		*root = new_node;
		return;
	}

	Node	*curr = *root;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_node;
}

void	insert_sorted(Node **root, int value)
{
	if (*root == NULL || (*root)->x >= value)			// same as (**root).x
	{
		insert_beginning(root, value);
		return;
	}
	Node *curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next->x >= value)
			break ;
		curr = curr->next;
	}
	insert_after(curr, value);
}

void	deallocate(Node **root)					// try to do it recursively
{
	if (!(*root))
		return ;
	Node *curr = *root;
	while (curr != NULL)
	{
		Node *aux = curr;
		curr = curr->next;
		free(aux);
	}
	*root = NULL;
}

void	remove_node(Node **root, int value)			// 1st occurence of the value
{
	if (*root == NULL)
		return ;
	if ((*root)->x == value)
	{
		Node *to_remove = *root;
		*root = (*root)->next;
		free(to_remove);
		return ;
	}

	Node *curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next->x == value)
		{
			Node *to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove);
			return ;
		}
		curr = curr->next;
	}
}

void	reverse(Node **root)				// try with previous fct + recursive manner
{
	Node *prev = NULL;
	Node *curr = *root;

	while (curr != NULL)
	{
		Node *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*root = prev;
}

int	has_loops(Node *root)
{
	Node *slow = root;
	Node *fast = root;

	while (slow != NULL && fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return 1;
	}
	return (0);
}

int	count(Node *root)
{
	int	i = 0;
	Node *curr = root;

	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
