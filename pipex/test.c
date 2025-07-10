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
		split[i] = NULL;
		i++;
	}
	free(split);
}

void ft_exit(t_data *data)
{
	if(data->fd != -1)
		close(data->fd);
	if (data->fd2 != -1)
		close(data->fd2);
	if (data->readed)
		free(data->readed);
	free_split(data->split1);
	free_split(data->split2);
	free(data);
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

void execute_command(char *cmd, char **envp)
{
	char **argv = ft_split(cmd, ' ');
	char *path = get_command_path(argv[0], envp);

	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(argv[0], 2);
		free_split(argv);
		exit(127);
	}

	if (execve(path, argv, envp) == -1)
	{
		perror("execve");
		free(path);
		free_split(argv);
		exit(1);
	}
}

int init(t_data *data, char **av)
{
	data->fd = -1;
	data->fd2 = -1;
	data->split1 = ft_split(av[2], ' ');
	data->split2 = ft_split(av[3], ' ');
	data->readed = calloc(1000, sizeof(char));
	data->file1 = av[1];
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->file2 = av[4];

	data->fd = open(data->file1, O_RDONLY);
	if (data->fd == -1)
	{
		perror("Error opening input file");
		return (1);
	}

	// ✅ Créer le fichier de sortie avec les bons flags
	data->fd2 = open(data->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd2 == -1)
	{
		close(data->fd);
		perror("Error opening output file");
		return (2);
	}
	return (0);
}

// ✅ Fonction pipex avec pipe et fork
void pipex(t_data *data, char **envp)
{
	int pipe_fd[2];
	pid_t pid1, pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}

	// Child process
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}

	if (pid1 == 0) // Premier enfant
	{
		close(pipe_fd[0]); // Ferme lecture
		dup2(data->fd, STDIN_FILENO); // Redirige stdin vers fichier d'entrée
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirige stdout vers pipe
		close(pipe_fd[1]);
		close(data->fd);

		execute_command(data->cmd1, envp);
	}

	// 2nd Child process
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}

	// 2nd Child process
	if (pid2 == 0)
	{
		close(pipe_fd[1]); // Ferme écriture
		dup2(pipe_fd[0], STDIN_FILENO); // Redirige stdin vers pipe
		dup2(data->fd2, STDOUT_FILENO); // Redirige stdout vers fichier de sortie
		close(pipe_fd[0]);
		close(data->fd2);

		execute_command(data->cmd2, envp);
	}

	// Processus parent
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	// Attendre les enfants
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int main(int ac, char** av, char **envp)
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

	// ✅ Maintenant on fait vraiment du piping !
	pipex(data, envp);

	ft_exit(data);
	return (0);
}
