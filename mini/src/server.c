// #include <signal.h>
// #include <stdio.h>
// #include <strings.h>
// #include <unistd.h>
// #include <stdlib.h>
#include "minitalk.h"
// receive signal from client

void	sig_handler(int sig)
{
	static int	bit = 8;
	static int	i;

	bit--;
	if (sig == SIGUSR2)
		i |= (0x01 << bit);
	if (bit == 0)
	{
		write(1, &i, 1);
		bit = 8;
		i = 0;
	}
	return ;
}

int	main(int ac, char	**av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Error: wrong format.\n");
		printf("Try: ./server\n");
		return (0);
	}
	printf("PID = %d\n", getpid());
	printf("Waiting...\n");
	while (ac == 1)
	{
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		pause();
	}
	return (0);
}
