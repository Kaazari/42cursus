#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include "../gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct	s_mlx_data {

	// int		color;
	void	*mlx;
	void	*win;
	int		fd;
	char	**map;
	int		x;			// width
	int		y;			// height

	void	*player;	// xpm
	void	*collectible;
	void	*wall;
	void	*floor;
	void	*exit;

	int		steps;		// stats
	int		collected;
	int		collectible_nb;
	int		exits;
	int		players;
	int		ccounter;
	int		px;			// player pos x_axis
	int		py;			// player pos y_axis
}				t_mlx_data;

// int		get_t(int trgb);
// int		get_r(int trgb);
// int		get_g(int trgb);
// int		get_b(int trgb);
// int		coloring(int t, int r, int g, int b);
// int		opposite(int color);
// int		add_shade(double shade, int color);
// void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

int		handler_2(t_mlx_data *data);
int		key(int keysym, t_mlx_data *data);
int		mapline(char **av, t_mlx_data *data);
int		map_reading(t_mlx_data *data, char **argv);
int		ft_exit(t_mlx_data *data);
int		controls(int command, t_mlx_data *data);
void	xpm_data(t_mlx_data	*data);
void	rendering(t_mlx_data *data);
void	map_check(t_mlx_data *data);void
init_struct(t_mlx_data *data);

#endif
