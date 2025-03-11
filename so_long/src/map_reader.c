#include <../include/so_long.h>

void	place(t_mlx_data *data, int h, int w)
{
	if (data->map[h][w] == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->exit, w * 32, h * 32);
	if (data->map[h][w] == '0')
		mlx_put_image_to_window(data->mlx, data->win,
			data->floor, w * 32, h * 32);
	if (data->map[h][w] == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->wall, w * 32, h * 32);
	if (data->map[h][w] == 'P')
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->player, w * 32, h * 32);
		data->px = w;
		data->py = h;
	}
	if (data->map[h][w] == 'C')
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->collectible, w * 32, h * 32);
		data->collectible_nb++;
	}
}

void	rendering(t_mlx_data *data)
{
	int	h;
	int	w;

	data->collectible_nb = 0;
	h = 0;
	while (h < data->y)
	{
		w = 0;
		while (data->map[h][w])
		{
			place(data, h, w);
			w++;
		}
		h++;
	}
}

char	**ft_copy(t_mlx_data *data)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = (char **)malloc(data->y * sizeof(char *));
	if (copy == NULL)
		return (NULL);
	while (i < data->y)
	{
		j = 0;
		copy[i] = (char *)malloc(data->x * sizeof(char));
		if (copy[i] == NULL)
			ft_exit(data);
		while (j++ < data->x)
			copy[i][j] = data->map[i][j];
		i++;
	}
	return (copy);
}

int	add(t_mlx_data *data, char *line, char **temp)
{
	int	i;

	if (!line)
		return (1);
	data->y++;
	temp = (char **)malloc(sizeof(char *) * (data->y + 1));
	temp[data->y] = NULL;
	data->x++;
	i = 0;
	while (i < data->y - 1)
	{
		temp[i] = data->map[i];
		i++;
	}
	temp[i] = line;
	if (data->map)
		free(data->map);
	data->map = temp;
	return (0);
}

int	mapline(char **av, t_mlx_data *data)
{
	char	**temp;
	char	*line;
	int		dir;

	dir = open(av[1], O_RDWR);
	if (dir < 0)
		return (1);
	close (dir);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
		return (1);
	temp = NULL;
	while (1)
	{
		line = get_next_line(data->fd);
		if (add(data, line, temp) == 1)
			break ;
	}
	data->x = ft_strlen(data->map[0]) - 1;
	close (data->fd);
	return (0);
}
