/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:04 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:05 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_initial_delay(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 10);
}

int	check_meals_completed(t_philo *philo)
{
	return (philo->data->must_eat_count != -1
		&& (int)++philo->meals_eaten == philo->data->must_eat_count);
}

int	handle_philosopher_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->finish_mutex);
	philo->finished = 1;
	philo->data->finished_count++;
	if (philo->data->finished_count == philo->data->philo_count)
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_unlock(&philo->data->death_mutex);
		check_death(philo->data, 2);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	handle_initial_delay(philo);
	while (!check_death(philo->data, 0))
	{
		pthread_create(&philo->death_thread, NULL, death_monitor, arg);
		eat_activity(philo);
		pthread_detach(philo->death_thread);
		if (check_meals_completed(philo) || philo->data->philo_count == 1)
		{
			if (handle_philosopher_finished(philo))
				return (NULL);
		}
	}
	return (NULL);
}
