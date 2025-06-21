#include "philo.h"

void	sleep_think(t_philo *philo)
{
	write_status("is sleeping\n", philo);
	precise_usleep(philo->data->time_to_sleep);
	write_status("is thinking\n", philo);
}

void	get_fork_order(t_philo *philo, pthread_mutex_t **first,
	pthread_mutex_t **second)
{
	if (&philo->left_fork < philo->right_fork)
	{
		*first = &philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = &philo->left_fork;
	}
}

void	handle_single_philosopher(t_philo *philo,
	pthread_mutex_t *first_fork)
{
	precise_usleep(philo->data->time_to_die * 2);
	pthread_mutex_unlock(first_fork);
}

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_usleep(philo->data->time_to_eat);
}

void	eat_activity(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	write_status("has taken a fork\n", philo);
	if (!philo->right_fork)
	{
		handle_single_philosopher(philo, first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	write_status("has taken a fork\n", philo);
	write_status("is eating\n", philo);
	eating_process(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	sleep_think(philo);
}
