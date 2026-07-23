#include <stdio.h>
#include <stdlib.h>

typedef struct s_map {
    int     height;    // nombre de lignes (lu depuis la première ligne du fichier)
    int     width;     // longueur d'une ligne (calculé à la lecture de la première ligne de map)
    char    empty;     // caractère "vide" ex: '.'
    char    obstacle;  // caractère "obstacle" ex: 'o'
    char    full;      // caractère "plein" ex: 'x'
    char    **grid;    // tableau 2D de strings = la map
} t_map;

static int	read_map(FILE *file, t_map *map)
{
	char	*line = NULL;
	size_t	capacity = 0;
	long	length;

	if (fscanf(file, "%d%c%c%c", &map->height, &map->empty, &map->obstacle,
			&map->full) != 4 || map->height < 1 || map->empty == map->obstacle
		|| map->empty == map->full || map->obstacle == map->full)
		return (0);
	if (getline(&line, &capacity, file) != 1 || *line != '\n')
		return (0);
	map->grid = calloc(map->height, sizeof *map->grid);
	for (int row = 0; row < map->height; row++)
	{
		line = NULL;
		capacity = 0;
		length = getline(&line, &capacity, file);
		if (length < 2 || line[length - 1] != '\n')
			return (0);
		line[--length] = '\0';
		if (row == 0)
			map->width = length;
		if (length != map->width)
			return (0);
		for (int col = 0; col < length; col++)
			if (line[col] != map->empty && line[col] != map->obstacle)
				return (0);
		map->grid[row] = line;
	}
	return (1);
}

static int	min3(int a, int b, int c)
{
	if (b < a)
		a = b;
	return (c < a ? c : a);
}

static void	solve(t_map *map)
{
	int	width = map->width;
	int	*sizes = calloc(map->height * width, sizeof *sizes);
	int	best_size = 0;
	int	best_row = 0;
	int	best_col = 0;

	for (int row = 0; row < map->height; row++)
		for (int col = 0; col < width; col++)
		{
			if (map->grid[row][col] == map->obstacle)
				continue ;
			if (row == 0 || col == 0)
				sizes[row * width + col] = 1;
			else
				sizes[row * width + col] = min3(sizes[(row - 1) * width + col],
						sizes[row * width + col - 1],
						sizes[(row - 1) * width + col - 1]) + 1;
			if (sizes[row * width + col] > best_size)
			{
				best_size = sizes[row * width + col];
				best_row = row - best_size + 1;
				best_col = col - best_size + 1;
			}
		}
	for (int row = best_row; row < best_row + best_size; row++)
		for (int col = best_col; col < best_col + best_size; col++)
			map->grid[row][col] = map->full;
}

int	main(int argc, char **argv)
{
	t_map	map = {0};
	FILE	*file = stdin;

	if (argc > 1 && !(file = fopen(argv[1], "r")))
		return (printf("Error: cannot open file\n"), 1);
	if (!read_map(file, &map))
		return (printf("Error: invalid map\n"), 1);
	solve(&map);
	for (int row = 0; row < map.height; row++)
	{
		fputs(map.grid[row], stdout);
		fputs("\n", stdout);
	}
	return (0);
}
