#include <../include/so_long.h>

void	init_struct(t_mlx_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->map = NULL;
	data->fd = 0;
	data->x = 0;
	data->y = 0;
	data->player = NULL;
	data->collectible = NULL;
	data->wall = NULL;
	data->floor = NULL;
	data->exit = NULL;
	data->steps = 0;
	data->collected = 0;
	data->collectible_nb = 0;
	data->exits = 0;
	data->players = 0;
	data->ccounter = 0;
	data->px = 0;
	data->py = 0;
}

int	what_if(t_mlx_data *data, int i, int j)
{
	if (data->map[j][i] == 'E')
	{
		if (data->collectible_nb != 0)
			return (0);
		printf("\nGG!\nYou made it in %i Steps!!\n\n", data->steps);
		ft_exit(data);
	}
	if (data->map[j][i] == 'C')
		data->collectible_nb--;
	data->map[j][i] = 'P';
	data->px = i;
	data->py = j;
	data->steps++;
	return (1);
}

int	key_w_s(t_mlx_data *data, int key)
{
	int	i;
	int	j;

	i = data->px;
	j = data->py;
	if (key == XK_w || key == XK_Up)
	{
		j--;
		if (data->map[j][i] == '1' || (!what_if(data, i, j)))
			return (0);
		data->map[j + 1][i] = '0';
	}
	else if (key == XK_s || key == XK_Down)
	{
		j++;
		if (data->map[j][i] == '1' || (!what_if(data, i, j)))
			return (0);
		data->map[j - 1][i] = '0';
	}
	printf("Steps : %i\n", data->steps);
	printf("To collect : %i\n", data->collectible_nb);
	return (1);
}

int	key_a_d(t_mlx_data *data, int key)
{
	int	i;
	int	j;

	i = data->px;
	j = data->py;
	if (key == XK_a || key == XK_Left)
	{
		i--;
		if (data->map[j][i] == '1' || (!what_if(data, i, j)))
			return (0);
		data->map[j][i + 1] = '0';
	}
	else if (key == XK_d || key == XK_Right)
	{
		i++;
		if (data->map[j][i] == '1' || (!what_if(data, i, j)))
			return (0);
		data->map[j][i - 1] = '0';
	}
	printf("Steps : %i\n", data->steps);
	printf("To collect : %i\n", data->collectible_nb);
	return (1);
}

int	controls(int key, t_mlx_data *data)
{
	int	works;

	works = 0;
	if (key == XK_Escape)
		ft_exit(data);
	if (key == XK_w || key == XK_Up)
		works = key_w_s(data, key);
	if (key == XK_a || key == XK_Left)
		works = key_a_d(data, key);
	if (key == XK_s || key == XK_Down)
		works = key_w_s(data, key);
	if (key == XK_d || key == XK_Right)
		works = key_a_d(data, key);
	if (works)
		rendering(data);
	return (1);
}
