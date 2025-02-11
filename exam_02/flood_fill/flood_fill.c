#include <stdlib.h>
#include <stdio.h>

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;


void	fill(char **tab, int y, int x, t_point size, char t)
{
	if (x >= size.x || x < 0 || y >= size.y || y < 0 || tab[y][x] != t)
		return ;
	tab[y][x] = 'F';
	fill(tab, y+1, x, size, t);
	fill(tab, y-1, x, size, t);
	fill(tab, y, x+1, size, t);
	fill(tab, y, x-1, size, t);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, begin.y, begin.x, size, tab[begin.y][begin.x]);
}


// ///////////////////////////////////////////////


// char** make_area(char** zone, t_point size)
// {
// 	char** new;

// 	new = malloc(sizeof(char*) * size.y);
// 	for (int i = 0; i < size.y; ++i)
// 	{
// 		new[i] = malloc(size.x + 1);
// 		for (int j = 0; j < size.x; ++j)
// 			new[i][j] = zone[i][j];
// 		new[i][size.x] = '\0';
// 	}

// 	return new;
// }

// int main(void)
// {
// 	t_point size = {8, 5};
// 	char *zone[] = {
// 		"11111111",
// 		"10001001",
// 		"10010001",
// 		"10110001",
// 		"11100001",
// 	};

// 	char**  area = make_area(zone, size);
// 	for (int i = 0; i < size.y; ++i)
// 		printf("%s\n", area[i]);
// 	printf("\n");

// 	t_point begin = {7, 4};
// 	flood_fill(area, size, begin);
// 	for (int i = 0; i < size.y; ++i)
// 		printf("%s\n", area[i]);
// 	return (0);
// }
