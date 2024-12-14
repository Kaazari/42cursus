#include <../include/so_long.h>

int	horizontalwall(t_mlx_data *data)
{
	int	i;
	int	j;

	i = data->x;
	j = 0;
	while (j < i)
	{
		if (data->map[0][i] == '1' && data->map[data->y - 1][j] == '1')
			return (0);
		j++;
	}
	return (1);
}

int	verticalwall(t_mlx_data *data)
{
	int	h;
	int	w;

	h = 0;
	w = data->x;
	while (h < data->y)
	{
		if (!(data->map[h][0] == '1' && data->map[h][w - 1] == '1'))
			return (0);
		h++;
	}
	return (1);
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
		data->players++;
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
	if (!verticalwall(data) || !horizontalwall(data))
	{
		printf("\nA wall is missing! Walls must border the maps.\n");
		ft_exit(data);
	}
	char_check(data);
}
