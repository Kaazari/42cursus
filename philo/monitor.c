#include "philo.h"

int	check_philosopher_death(t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	return (!philo->data->dead && !philo->finished
		&& ((current_time - philo->last_meal_time)
			>= (long)(philo->data->time_to_die)));
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	precise_usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (check_philosopher_death(philo))
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_death_message(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	return (NULL);
}
