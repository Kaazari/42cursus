#include "pipex.h"

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		**pipe_fds;	// Tableau de pipes
	int		num_pipes;	// Nombre de pipes nécessaires
	int		infile_fd;
	int		outfile_fd;
}	t_pipex;


void free_split(char **split)
{
	int i;
	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

// Fonction pour calculer le nombre de pipes nécessaires
int	calculate_pipes(int argc)
{
	// argc = ./pipex file1 cmd1 cmd2 cmd3 file2
	// Nombre de commandes = argc - 3
	// Nombre de pipes = nombre de commandes - 1
	return (argc - 4);
}

char *get_path_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// ✅ Version corrigée sans fuite mémoire
char *get_command_path(char *cmd, char **envp)
{
	char *path_env;
	char **paths;
	char *full_path;
	char *temp;
	int i = 0;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':');
	while (paths[i])
	{
		// ✅ Correction de la fuite mémoire
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp); // ✅ Libère la première allocation

		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

// Créer tous les pipes nécessaires
int	**create_pipes(int num_pipes)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = malloc(sizeof(int *) * num_pipes);
	if (!pipe_fds)
		return (NULL);

	i = 0;
	while (i < num_pipes)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!pipe_fds[i] || pipe(pipe_fds[i]) == -1)
		{
			// Nettoyer en cas d'erreur
			while (--i >= 0)
			{
				close(pipe_fds[i][0]);
				close(pipe_fds[i][1]);
				free(pipe_fds[i]);
			}
			free(pipe_fds);
			return (NULL);
		}
		i++;
	}
	return (pipe_fds);
}

// Fermer tous les pipes dans le processus parent
void	close_all_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->num_pipes)
	{
		close(data->pipe_fds[i][0]);
		close(data->pipe_fds[i][1]);
		i++;
	}
}

// Exécuter une commande avec les bonnes redirections
void	execute_command(t_pipex *data, int cmd_index)
{
	int		total_cmds;
	char	**cmd_args;
	char	*cmd_path;

	total_cmds = data->argc - 3;
	cmd_args = ft_split(data->argv[cmd_index + 2], ' ');
	cmd_path = get_command_path(cmd_args[0], data->envp);

	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		free_split(cmd_args);
		exit(127);
	}

	// Redirection d'entrée
	if (cmd_index == 0)
	{
		// Première commande : lit depuis le fichier d'entrée
		dup2(data->infile_fd, STDIN_FILENO);
	}
	else
	{
		// Autres commandes : lisent depuis le pipe précédent
		dup2(data->pipe_fds[cmd_index - 1][0], STDIN_FILENO);
	}

	// Redirection de sortie
	if (cmd_index == total_cmds - 1)
	{
		// Dernière commande : écrit vers le fichier de sortie
		dup2(data->outfile_fd, STDOUT_FILENO);
	}
	else
	{
		// Autres commandes : écrivent vers le pipe suivant
		dup2(data->pipe_fds[cmd_index][1], STDOUT_FILENO);
	}

	// Fermer tous les pipes (plus nécessaires après dup2)
	close_all_pipes(data);
	close(data->infile_fd);
	close(data->outfile_fd);

	// Exécuter la commande
	execve(cmd_path, cmd_args, data->envp);
	perror("execve");
	exit(1);
}

// Fonction principale du bonus
void	pipex_bonus(t_pipex *data)
{
	pid_t	*pids;
	int		total_cmds;
	int		i;

	total_cmds = data->argc - 3;
	pids = malloc(sizeof(pid_t) * total_cmds);
	if (!pids)
		return ;

	// Créer un processus pour chaque commande
	i = 0;
	while (i < total_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pids[i] == 0)
		{
			// Processus enfant
			execute_command(data, i);
		}
		i++;
	}

	// Processus parent : fermer tous les pipes
	close_all_pipes(data);
	close(data->infile_fd);
	close(data->outfile_fd);

	// Attendre tous les enfants
	i = 0;
	while (i < total_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}

	free(pids);
}

// Initialiser la structure pour le bonus
int	init_bonus(t_pipex *data, int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2", 2);
		return (1);
	}

	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->num_pipes = calculate_pipes(argc);

	// Ouvrir fichiers d'entrée et de sortie
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror("Error opening input file");
		return (1);
	}

	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		close(data->infile_fd);
		perror("Error opening output file");
		return (1);
	}

	// Créer tous les pipes
	data->pipe_fds = create_pipes(data->num_pipes);
	if (!data->pipe_fds)
	{
		close(data->infile_fd);
		close(data->outfile_fd);
		return (1);
	}

	return (0);
}

// Nettoyer les ressources
void	cleanup_bonus(t_pipex *data)
{
	int	i;

	if (data->pipe_fds)
	{
		i = 0;
		while (i < data->num_pipes)
		{
			free(data->pipe_fds[i]);
			i++;
		}
		free(data->pipe_fds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (init_bonus(&data, argc, argv, envp))
		return (1);

	pipex_bonus(&data);

	cleanup_bonus(&data);
	return (0);
}
