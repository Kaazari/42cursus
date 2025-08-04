#include "philo.h"

void	sync_start(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->philo_count % 2 == 0)
		i = 0;
	else
		i = 1;
	if (philo->id % 2 == 0 && i == 0)
		usleep(100);
	if (philo->id % 2 == 1 && i == 1)
		usleep(100);
	return ;
}

void	*start_routine(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->time_start = get_time();
	while (i < philo->data->philo_count)
	{
		sync_start(&philo[i]);
		pthread_create(&philo[i].thread_id, NULL, routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&philo->data->death_monitor,
		NULL, death_monitor, (void *)philo);
	while (i < philo->data->philo_count)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(philo->data->death_monitor, NULL);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->last_meal_time == 0)
		philo->last_meal_time = get_time();
	while (!death_status(philo->data) || !philo->data->all_eat)
	{
		eat(philo);
		if (philo->data->all_eat || death_status(philo->data))
			break ;
		time_to_sleep(philo);
		if (philo->data->all_eat || death_status(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (check_args(ac, av))
		data = malloc(sizeof(t_data));
	else
		return (0);
	philo = malloc(sizeof(t_philo) * (atoi_strict(av[1]) + 1));
	init_data_struct(ac, av, data);
	init_philo(philo, data);
	if (data->philo_count > 1)
	{
		start_routine(philo);
		usleep(10000);
		cleanup_all(philo);
	}
	else
		one_philo(philo);
	return (0);
}
