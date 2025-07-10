#include "minishell.h"

char **tokenize_input(char *input) {
	char **args = malloc(sizeof(char *) * 64); // Max 64 arguments
	char *token;
	int i = 0;

	if (!args) {
		perror("malloc");
		return NULL;
	}

	// Tokenisation simple avec des espaces
	token = strtok(input, " \t\n");
	while (token != NULL && i < 63) {
		args[i] = malloc(strlen(token) + 1);
		if (!args[i]) {
			perror("malloc");
			return NULL;
		}
		strcpy(args[i], token);
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL; // Terminateur

	return args;
}



void free_args(char **args) {
	if (!args) return;

	for (int i = 0; args[i]; i++) {
		free(args[i]);
	}
	free(args);
}
