#include "minishell.h"

void builtin_cd(char **args) {
    char *path;
    if (args[1] == NULL) {
        path = getenv("HOME");
    } else if (strcmp(args[1], "-") == 0) {
        path = getenv("OLDPWD");
    } else {
        path = args[1];
    }

    if (path && chdir(path) != 0) {
        perror("cd");
    }
}

void builtin_pwd(char **args) {
    (void)args;
    char *cwd = getcwd(NULL, 0);
    if (cwd) {
        printf("%s\n", cwd);
        free(cwd);
    } else {
        perror("pwd");
    }
}

void builtin_exit(char **args) {
    int exit_code = 0;
    if (args[1] != NULL) {
        exit_code = atoi(args[1]);
    }
    printf("exit\n");
    exit(exit_code);
}

void builtin_unset(char **args, t_shell *shell) {
    (void)shell; // À implémenter plus tard avec votre propre env
    if (args[1] == NULL) {
        printf("unset: not enough arguments\n");
        return;
    }
    // Pour l'instant, on ne peut pas vraiment unset sans unsetenv
    printf("unset: %s (not implemented)\n", args[1]);
}

void builtin_echo(char **args) {
    int i = 1;
    int nline = 1;

    if (args[1] && strcmp(args[1], "-n") == 0) {
        nline = 0;
        i = 2;
    }

    while (args[i]) {
        printf("%s", args[i]);
        if (args[i + 1]) printf(" ");
        i++;
    }
    if (nline) printf("\n");
}

void builtin_env(char **args, t_shell *shell) {
    (void)args;
    for (int i = 0; shell->envp[i]; i++) {
        printf("%s\n", shell->envp[i]);
    }
}

void builtin_export(char **args, t_shell *shell) {
    if (!args[1]) {
        print_export_format(shell->envp);
        return;
    }

    for (int i = 1; args[i]; i++) {
        if (strchr(args[i], '=')) {
            add_or_update_env(args[i], shell);
        } else {
            export_existing_var(args[i], shell);
        }
    }
}
