// #include <signal.h>
// #include <stdio.h>
// #include <strings.h>
// #include <unistd.h>
// #include <stdlib.h>
#include "minitalk.h"
// send signal to serv

void	ascii_to_bits(pid_t pid, char c)
{
	int	bits;
	int	mask;

	bits = 7;
	mask = 0;
	while (bits >= 0)
	{
		mask = (1 << bits);
		if (c & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(2000);
		bits--;
	}
	return ;
}

int	main(int ac, char	**av)
{
	int	i;

	i = 0;
	if (ac == 3)
		while (av[2][i] != 0)
			ascii_to_bits(atoi(av[1]), av[2][i++]);
	else
	{
		printf("Error: wrond format.\n");
		printf("Right format: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	ascii_to_bits(atoi(av[1]), '\n');
	return (0);
}
