#include "pipex.h"

void	ft_exit(t_data *data)
{
	if(data->fd != -1)
		close(data->fd);
	if (data->fd2 != -1)
		close(data->fd2);
	// if ()
}

int	init(t_data *data, char **av)
{

	data = memset(&data, 0, sizeof(t_data));
	data->readed = calloc(100, sizeof(char));
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
	return (0);cd 
}

int	main(int ac, char** av)
{
	if(ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		return (1);
	}
	t_data *data;
	if (init)
		return (1);

	int rd = read(data->fd, data->readed, 100);
	write(data->fd2, data->readed, ft_strlen(data->readed));
	printf("%s\n", data->readed);
	close(data->fd);
	return (0);
}
