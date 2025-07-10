#include "minishell.h"

char *find_command_in_path(char *command) {
	char *path_env = getenv("PATH");
	char *path_copy;
	char *dir;
	char *full_path;

	if (!path_env) return NULL;

	path_copy = malloc(strlen(path_env) + 1);
	if (!path_copy) return NULL;
	strcpy(path_copy, path_env);

	dir = strtok(path_copy, ":");
	while (dir != NULL) {
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path) {
			free(path_copy);
			return NULL;
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0) {
			free(path_copy);
			return full_path;
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}

void print_export_format(char **envp) {
	for (int i = 0; envp[i]; i++) {
		printf("declare -x %s\n", envp[i]);
	}
}

// Version simple - utilise setenv (pas dans la liste mais nécessaire)
void add_or_update_env(char *var, t_shell *shell) {
	(void)shell; // Pour l'instant, on utilise setenv
	char *equal_pos = strchr(var, '=');
	if (equal_pos) {
		*equal_pos = '\0';
		setenv(var, equal_pos + 1, 1);
		*equal_pos = '='; // Restaurer
	}
}

void export_existing_var(char *var, t_shell *shell) {
	(void)shell; // Pour l'instant, on utilise getenv
	char *value = getenv(var);
	if (value) {
		setenv(var, value, 1);
	}
}
