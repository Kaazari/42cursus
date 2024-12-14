#include "minitalk_bonus.h"
// receive sigaction from client

void	sig_handler(int sig, siginfo_t *info, void *o)
{
	static int	bit = 8;
	static int	i;

	bit--;
	(void)o;
	(void)info;
	if (sig == SIGUSR2)
		i |= (0x01 << bit);
	if (bit == 0)
	{
		write(1, &i, 1);
		bit = 8;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
	return ;
}

int	main(int ac, char	**av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		printf("Error: wrong format.\n");
		printf("Try: ./server\n");
		return (0);
	}
	printf("PID = %d\n", getpid());
	printf("Waiting...\n");
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	while (ac == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
