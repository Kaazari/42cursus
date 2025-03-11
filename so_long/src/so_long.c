#include <../include/so_long.h>

//////////////////////////////////////////////////////////////////////////////

void	xpm_data(t_mlx_data *data)
{
	int	i;
	int	j;

	data->player = mlx_xpm_file_to_image(data->mlx, "files/player.xpm", &i, &j);
	if (!data->player)
		ft_exit(data);
	data->exit = mlx_xpm_file_to_image(data->mlx, "files/exit.xpm", &i, &j);
	if (!data->exit)
		ft_exit(data);
	data->floor = mlx_xpm_file_to_image(data->mlx, "files/floor.xpm", &i, &j);
	if (!data->floor)
		ft_exit(data);
	data->wall = mlx_xpm_file_to_image(data->mlx, "files/wall.xpm", &i, &j);
	if (!data->wall)
		ft_exit(data);
	data->collectible = mlx_xpm_file_to_image(data->mlx,
			"files/clt.xpm", &i, &j);
	if (!data->collectible)
		ft_exit(data);
}

int	fd_check(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 4;
	if (!s1 || j <= 0)
		return (1);
	while (s1[j] == s2[i] && s1[j] && s2[i])
	{
		i++;
		j++;
	}
	if (s1[j] - s2[i] != 0)
		return (1);
	return (0);
}

int	ft_exit(t_mlx_data *data)
{
	int	line;

	line = 0;
	while (line < data->y - 1)
		free(data->map[line++]);
	free(data->map);
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, data->player);
		mlx_destroy_image(data->mlx, data->collectible);
		mlx_destroy_image(data->mlx, data->wall);
		mlx_destroy_image(data->mlx, data->floor);
		mlx_destroy_image(data->mlx, data->exit);
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}
// free(data->mlx); to free all --> also causes an invalid free

void	ff_path(t_mlx_data *data, int px, int py, char filler)
{
	if ((py < 0 || py >= data->y || px < 0 || px >= data->x)
		|| ((data->copy[py][px] != filler && data->copy[py][px] != 'C'
		&& data->copy[py][px] != 'E')))
		return ;
	if (data->copy[py][px] == 'C' || data->copy[py][px] == 'E')
	{
		if (data->copy[py][px] == 'C')
			data->ff_collect++;
		if (data->copy[py][px] == 'E')
			data->ff_exit++;
		data->copy[py][px] = filler;
	}
	data->copy[py][px] = 'F';
	ff_path(data, px + 1, py, filler);
	ff_path(data, px - 1, py, filler);
	ff_path(data, px, py + 1, filler);
	ff_path(data, px, py - 1, filler);
}

int	main(int ac, char	**av)
{
	t_mlx_data	data;

	if (ac != 2 || fd_check(av[1], ".ber") == 1)
	{
		printf("Error.\nTry this : ./so_long YourMap.ber\n");
		return (1);
	}
	init_struct(&data);
	mapline(av, &data);
	map_check(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.x * 32, data.y * 32, "so_long");
	if (!data.win)
		ft_exit(&data);
	xpm_data(&data);
	rendering(&data);
	mlx_key_hook(data.win, controls, &data);
	mlx_hook(data.win, 17, 0, ft_exit, &data);
	mlx_loop(data.mlx);
}
