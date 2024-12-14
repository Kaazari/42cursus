#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Node {
	int				x;
	struct Node		*next;
} Node;

void	deallocate(Node **root)					// try to do it recursively
{
	Node *curr = *root;
	while (curr != NULL)
	{
		Node *aux = curr;
		curr = curr->next;
		free(aux);
	}
	*root = NULL;
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

int	main(int ac, char **av)
{
	Node	*root = malloc(sizeof(Node));
	if (root == NULL)
		exit(2);
	root->x = 15;
	root->next = NULL;

	insert_end(&root, -2);
	insert_end(&root, 11);
	insert_end(&root, 22);

	Node	*curr = root;
	while (curr != NULL)
	{
		printf("%d\n", curr->x);
		curr = curr->next;
	}

	deallocate(&root);
	return (0);
}
