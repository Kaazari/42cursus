#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

// compute the distance between two points
float	distance(float a[2], float b[2])
{
	return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

float	calculate_circuit_distance(float(*array)[2], int *path, int size)
{
	float total = 0.0f;
	int i = 0;
	while (i < size - 1)
	{
		total = total + distance(array[path[i]], array[path[i + 1]]);
		i++;
	}
	return (total);
}

void	tsp_backtrack(float (*array)[2], int *path, int *used, int pos, int size, float *best)
{
	int i;
	if (pos == size)
	{
		float dist = calculate_circuit_distance(array, path, size);
		if (dist < *best)
			*best = dist;
		return ;
	}
	i = 0;
	while (i < size)
	{
		if (!used[i])
		{
			used[i] = 1;
			path[pos] = i;
			tsp_backtrack(array, path, used, pos + 1, size, best);
			used[i] = 0;
		}
	}
}

float tsp(float (*array)[2], ssize_t size)
{
	float best_distance = 999999999.0f;
	int path[11];
	int used[11];
	int i = 0;
	while (i < size)
	{
		used[i] = 0;
	}
	tsp_backtrack(array, path, used, 0, size, &best_distance);
	return (best_distance);
}










/////////////////////////
////////////////////////////
///////////////////////////////










ssize_t	file_size(FILE *file)
{
	char	*buffer = NULL;
	size_t	n = 0;
	ssize_t ret;

	errno = 0;

	for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

	free(buffer);
	if (errno || fseek(file, 0, SEEK_SET))
		return -1;
	return ret;
}

int		retrieve_file(float (*array)[2], FILE *file)
{
	int tmp;
	for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
		if (tmp != 2)
		{
			errno = EINVAL;
			return -1;
		}
	if (ferror(file))
		return -1;
	return 0;
}

int		main(int ac, char **av)
{
	char *filename = "stdin";
	FILE *file = stdin;
	if (ac > 1)
	{
		filename = av[1];
		file = fopen(filename, "r");
	}

	if (!file)
	{
		fprintf(stderr, "Error opening %s: %m\n", filename);
		return 1;
	}

	ssize_t size = file_size(file);
	if (size == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", filename);
		fclose(file);
		return 1;
	}

	float (*array)[2] = calloc(size, sizeof (float [2]));
	if (!array)
	{
		fprintf(stderr, "Error: %m\n");
		fclose(file);
		return 1;
	}

	if (retrieve_file(array, file) == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", av[1]);
		fclose(file);
		free(array);
		return 1;
	}
	if (ac > 1)
		fclose(file);

	printf("%.2f\n", tsp(array, size));
	free(array);
	return (0);
}
