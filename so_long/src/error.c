#include <../include/so_long.h>

int	horizontalwall(t_mlx_data *data)
{
	int	j;

	j = 0;
	while (j < data->x)
	{
		if (data->map[0][j] != '1' || data->map[data->y - 1][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	verticalwall(t_mlx_data *data)
{
	int	h;

	h = 0;
	while (h < data->y)
	{
		if (data->map[h][0] != '1' || data->map[h][data->x - 1] != '1')
			return (1);
		h++;
	}
	return (0);
}

void	count_checker(t_mlx_data *data, int h, int w)
{
	if (data->map[h][w] != '1' &&
		data->map[h][w] != '0' &&
		data->map[h][w] != 'P' &&
		data->map[h][w] != 'E' &&
		data->map[h][w] != 'C' &&
		data->map[h][w] != '\n')
	{
		printf("\nThe %c character is not allowed!\n", data->map[h][w]);
		printf("Allowed characters : C, E, P, 0, 1.\n");
		ft_exit(data);
	}
	if (data->map[h][w] == 'C')
		data->ccounter++;
	if (data->map[h][w] == 'P')
	{
		data->players++;
		data->px = w;
		data->py = h;
	}
	if (data->map[h][w] == 'E')
		data->exits++;
}

void	char_check(t_mlx_data *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < data->y - 1)
	{
		w = 0;
		while (w <= data->x)
		{
			count_checker(data, h, w);
			w++;
		}
		h++;
	}
	if (data->players != 1)
		printf("You do not have the correct amount of players.\n");
	if (data->ccounter < 1)
		printf("You do not have the correct amount of collectibles.\n");
	if (data->exits != 1)
		printf("You do not have the correct amount of exits.\n");
	if (data->players != 1 || data->ccounter < 1 || data->exits != 1)
		ft_exit(data);
}

void	map_check(t_mlx_data *data)
{
	if (verticalwall(data) == 1 || horizontalwall(data) == 1)
	{
		printf("\nA wall is missing! Walls must border the maps.\n");
		ft_exit(data);
	}
	char_check(data);
	data->copy = ft_copy(data);
	data->copy[data->py][data->px] = '0';
	ff_path(data, data->px, data->py, data->copy[data->py][data->px]);
	while (*data->copy)
		free(*data->copy++);
	free(data->copy);
	if (data->ff_collect != data->ccounter)
		printf("All the collectibles cannot be reached.\n");
	if (!data->ff_exit)
		printf("The exit cannot be reached.\n");
	if (!data->ff_exit || data->ff_collect != data->ccounter)
		ft_exit(data);
}
