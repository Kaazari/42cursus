#include "minitalk_bonus.h"
// send signal to serv
int	g_end;

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
		usleep(100);
		bits--;
	}
	return ;
}

static void	sig_handler(int sig)
{
	if (sig == SIGUSR2 && g_end == 0)
		printf("Received!\n");
	return ;
}

int	main(int ac, char	**av)
{
	int	i;

	i = 0;
	if (ac == 3)
	{
		while (av[2][i] != 0)
		{
			signal(SIGUSR2, sig_handler);
			ascii_to_bits(atoi(av[1]), av[2][i++]);
			g_end = av[2][i - 1];
		}
	}
	else
	{
		printf("Error: wrong format.\n");
		printf("Right format: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	ascii_to_bits(atoi(av[1]), '\n');
	return (0);
}
