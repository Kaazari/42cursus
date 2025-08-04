#include "philo.h"

void	eat(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->forks[left_fork(philo->left_fork,
			philo->right_fork)]);
	pthread_mutex_lock(&philo->data->forks[right_fork(philo->left_fork,
			philo->right_fork)]);
	write_status(philo, "has taken a fork");
	write_status(philo, "has taken a fork");
	(*philo).meals_eaten += 1;
	write_status(philo, "is eating");
	ft_usleep((*philo).data->time_to_eat);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	pthread_mutex_unlock(&philo->data->forks[left_fork(philo->left_fork,
			philo->right_fork)]);
	pthread_mutex_unlock(&philo->data->forks[right_fork(philo->left_fork,
			philo->right_fork)]);
}

void	time_to_sleep(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return ;
	write_status(philo, "is sleeping..." );
	ft_usleep((*philo).data->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return ;
	write_status(philo, "is thinking...");
}

void	write_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (death_status(philo->data) == 1 || philo->data->all_eat == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%llu %d %s\n",
		time_to_print(philo->data->time_start), philo->id, s);
	usleep(6);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	cleanup_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_count)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->time_mutex);
	pthread_mutex_destroy(&philo->data->eat_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->death_mutex);
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}
