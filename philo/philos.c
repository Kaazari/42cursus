#include "philo.h"

int	death_status(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(1);
	if (philo->data->must_eat_count > 0)
	{
		while (!philo->data->all_eat && !death_status(philo->data))
		{
			if (is_dead(philo) || philo->data->all_eat)
				break ;
			if (check_full(philo))
				break ;
		}
	}
	else
	{
		while (death_status(philo->data) == 0)
		{
			if (is_dead(philo))
				break ;
		}
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	long long	dead_time;
	long long	time_now;
	int			ret;

	dead_time = (long long)philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->time_mutex);
	time_now = get_time();
	pthread_mutex_unlock(&philo->data->time_mutex);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	ret = death_check(philo, dead_time, time_now);
	if (ret == 0)
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
	return (ret);
}

int	check_full(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->data->philo_count && !death_status(philo->data))
	{
		if (philo[i].meals_eaten == philo->data->must_eat_count)
			j += 1;
		i++;
	}
	if (j == philo->data->philo_count)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->all_eat = 1;
		printf("All philosophers ate %d times.\n", philo->data->all_eat);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

int	death_check(t_philo *philo, long long death_time, long long n)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_count)
	{
		if (n - philo[i].last_meal_time > death_time)
		{
			pthread_mutex_lock(&philo->data->print_mutex);
			pthread_mutex_lock(&philo->data->death_mutex);
			printf("%llu %d died.\n",
				time_to_print(philo->data->time_start), philo[i].id);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			pthread_mutex_unlock(&philo->data->print_mutex);
			pthread_mutex_unlock(&philo->data->last_meal_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
