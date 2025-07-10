#ifndef MINISHELL_h
# define MINISHEL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include "libft/libft.h"

typedef struct s_shell {
	char	**envp;
	char	**args;
} t_shell;

// Fonctions principales
void execute_command(char **args, t_shell *shell);
void execute_external_commands(char **args, char **envp);

// Parsing
char **tokenize_input(char *input);
void free_args(char **args);

// Utils
char *find_command_in_path(char *command);
void print_export_format(char **envp);
void add_or_update_env(char *var, t_shell *shell);
void export_existing_var(char *var, t_shell *shell);

// Builtins
void builtin_cd(char **args);
void builtin_pwd(char **args);
void builtin_export(char **args, t_shell *shell);
void builtin_unset(char **args, t_shell *shell);
void builtin_env(char **args, t_shell *shell);
void builtin_exit(char **args);
void builtin_echo(char **args);

// Token
int is_separator(char c);
int is_quote(char c);
char handle_quote_state(char c, char current_quote);
void add_char_to_word(char **word, int *pos, char c);
void add_char_to_token(char **token, int *pos, int *size, char c);
void save_token(char ***args, int *arg_count, char *token, int token_pos);
char *expand_variable(char *var_name);
int process_variable(char *input, int i, char **token, int *pos, int *size);

#endif
