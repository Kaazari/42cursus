/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_death(philo->data, 0))
	{
		pthread_mutex_lock(&philo->data->time_eat_mutex);
		if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->time_eat_mutex);
			check_death(philo->data, 1);
			write_status("died", philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->time_eat_mutex);
		ft_usleep(1);
	}
	return (NULL);
}

int	check_all_philosophers_death(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo < data->philo + data->philo_count)
	{
		if (check_philosopher_death(philo))
		{
			announce_death(data, philo->id);
			return (1);
		}
		philo++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_all_philosophers_death(data))
			return (NULL);
		if (data->must_eat_count != -1 && all_philosophers_ate_enough(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_mutex);
			announce_finish(data);
			return (NULL);
		}
		ft_usleep(1);
	}
}

int	check_philosopher_death(t_philo *philo)
{
	int	death;

	death = 0;
	pthread_mutex_lock(&philo->data->time_eat_mutex);
	if (philo->last_meal_time + philo->data->time_to_die < get_time())
		death = 1;
	pthread_mutex_unlock(&philo->data->time_eat_mutex);
	return (death);
}

int	all_philosophers_ate_enough(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo < data->philo + data->philo_count)
	{
		pthread_mutex_lock(&data->time_eat_mutex);
		if (philo->meals_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->time_eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->time_eat_mutex);
		philo++;
	}
	return (1);
}
