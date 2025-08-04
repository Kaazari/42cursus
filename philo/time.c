#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	time_to_print(long long start_time)
{
	if (start_time > 0)
		return (get_time() - start_time);
	return (0);
}

void	ft_usleep(long int time_ms)
{
	long int	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_ms)
		usleep(100);
}
