#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long long time_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_ms)
		usleep(time_ms / 10);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->threads[i], NULL, philo_routine,
				&data->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	wait_for_completion(t_data *data)
{
	int	i;

	while (!check_death(data, 0))
		precise_usleep(1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	if (data->dead == 2 && data->must_eat_count != -1)
		printf("Each philosopher ate %d time(s)\n", data->must_eat_count);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_arguments(argc, argv, &data))
		return (1);
	if (allocate_memory(&data))
		return (1);
	if (init_mutexes(&data) || init_philosophers(&data))
	{
		cleanup(&data);
		return (1);
	}
	if (create_threads(&data))
	{
		destroy_mutexes(&data);
		cleanup(&data);
		return (1);
	}
	wait_for_completion(&data);
	destroy_mutexes(&data);
	cleanup(&data);
	return (0);
}
