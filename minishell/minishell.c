#include "minishell.h"

void execute_external_commands(char **args, char **envp)
{
	pid_t pid = fork();
	if (pid == 0) {
		// Processus enfant
		if (execve(args[0], args, envp) == -1) {
			// Si execve échoue, essayer avec PATH
			char *cmd_path = find_command_in_path(args[0]);
			if (cmd_path) {
				execve(cmd_path, args, envp);
				free(cmd_path);
			}
			perror(args[0]); // Affiche l'erreur
			exit(127); // Code d'erreur standard
		}
	} else if (pid > 0) {
		// Processus parent
		wait(NULL); // Attendre que l'enfant se termine
	} else {
		perror("fork");
	}
}

void execute_command(char **args, t_shell *shell) {
	if (!args || !args[0])
		return ;
	if (strcmp(args[0], "cd") == 0)
		builtin_cd(args);
	else if (strcmp(args[0], "pwd") == 0)
		builtin_pwd(args);
	else if (strcmp(args[0], "export") == 0)
		builtin_export(args, shell);
	else if (strcmp(args[0], "unset") == 0)
		builtin_unset(args, shell);
	else if (strcmp(args[0], "env") == 0)
		builtin_env(args, shell);
	else if (strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else if (strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else
		execute_external_commands(args, shell->envp);
}

int main(int ac, char **av, char **envp) {
	(void)ac;
	(void)av;
	t_shell shell;
	shell.envp = envp;
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input) {
			printf("exit\n");
			break;
		}
		if (strlen(input) == 0) {
			free(input);
			continue;
		}

		// Tokenisation améliorée
		shell.args = tokenize_input(input);
		if (shell.args) {
			execute_command(shell.args, &shell);
			free_args(shell.args); // Libérer la mémoire
		}
		free(input);
	}
	return (0);
}
