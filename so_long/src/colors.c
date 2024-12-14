#include <../include/so_long.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	coloring(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	opposite(int color)
{
	int	white;

	white = coloring(0, 255, 255, 255);
	return (white - color);
}

int	add_shade(double shade, int color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (shade > 1)
		return (0);
	t = get_t(color) * shade;
	r = get_r(color) * shade;
	g = get_g(color) * shade;
	b = get_b(color) * shade;
	return (coloring(t, r, g, b));
}
