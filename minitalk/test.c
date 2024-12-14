#include <stdio.h>

int	main()
{
	char c = 'X';
	int	bits;
	int	mask;

	bits = 7;
	mask = 0;
	while (bits >= 0)
	{
		mask = (1 << bits);
		printf("mask = %d\n", mask);
		if (c & mask)
			printf("c & mask\n");
		else
			printf("NO\n");
		bits--;
	}
	return 0;
}
