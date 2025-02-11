#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int n = end - start;
	int step = 1;

	if (n < 0)
		n *= -1;
	n++;

	int	*arr = (int *)malloc(sizeof(int) * n);
	if (arr)
	{
		int i = 0;
		if (start < end)
			step = -1;
		while (i < n)
		{
			arr[i] = end;
			end = end + step;
			i++;
		}
	}
	return (arr);
}
