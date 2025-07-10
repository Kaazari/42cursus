#include "pipex.h"

void free_split(char **split)
{
	int i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL; // Évite les double-free
		i++;
	}
	free(split);
}

void	ft_exit(t_data *data)
{
	if(data->fd != -1)
		close(data->fd);
	if (data->fd2 != -1)
		close(data->fd2);
	free_split(data->split1);
	free_split(data->split2);
	// if (data->split1)
	// 	free(data->split1);
	// if (data->split2)
	// 	free(data->split2);
}

// Récupérer la variable PATH de l'environnement
char *get_path_env(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5); // Retourne après "PATH="
		i++;
	}
	return (NULL);
}

// Trouver le chemin complet d'une commande
char *get_command_path(char *cmd, char **envp)
{
	char *path_env;
	char **paths;
	char *full_path;
	int i = 0;

	// Si la commande contient déjà un '/', c'est un chemin absolu
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':'); // Séparer par ':'

	while (paths[i])
	{
		// Construire le chemin complet : "/bin" + "/" + "ls"
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd); // Attention aux fuites mémoire !

		// Tester si le fichier existe et est exécutable
		if (access(full_path, X_OK) == 0)
		{
			// Libérer paths avant de retourner
			free_split(paths);
			return (full_path);
		}

		free(full_path);
		i++;
	}

	free_split(paths);
	return (NULL); // Commande non trouvée
}

void execute_command(char *cmd, char **envp)
{
	char **argv = ft_split(cmd, ' ');
	char *path = get_command_path(argv[0], envp);

	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(argv[0], 2);
		exit(127);
	}

	if (execve(path, argv, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

int	init(t_data *data, char **av)
{
	data->split1 = ft_split(av[2], ' ');
	data->split2 = ft_split(av[3], ' ');
	data->readed = calloc(1000, sizeof(char));
	data->file1 = av[1];
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->file2 = av[4];
	data->fd = open(data->file1, O_RDONLY);
	if (data->fd == -1)
		return (1);
	data->fd2 = open(data->file2, O_WRONLY);
	if (data->fd2 == -1)
	{
		close(data->fd);
		return (2);
	}
	return (0);
}

// void	pipex(t_data *data)
// {
// 	pipe(data->pipe_fd);
// }

int	main(int ac, char** av, char **envp)
{
	if(ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		return (1);
	}
	t_data *data = calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	if (init(data, av))
	{
		ft_exit(data);
		return (1);
	}
	// pipex(data, envp);
	ft_exit(data);
	return (0);
}
