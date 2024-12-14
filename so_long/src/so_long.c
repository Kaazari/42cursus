#include <../include/so_long.h>

//////////////////////////////////////////////////////////////////////////////

void	xpm_data(t_mlx_data *data)
{
	int	i;
	int	j;

	data->player = mlx_xpm_file_to_image(data->mlx, "files/player.xpm", &i, &j);
	data->exit = mlx_xpm_file_to_image(data->mlx, "files/exit.xpm", &i, &j);
	data->floor = mlx_xpm_file_to_image(data->mlx, "files/floor.xpm", &i, &j);
	data->wall = mlx_xpm_file_to_image(data->mlx, "files/wall.xpm", &i, &j);
	data->collectible = mlx_xpm_file_to_image(data->mlx,
			"files/clt.xpm", &i, &j);
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
// free(data->mlx); to free all -> also an invalid free

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
