/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		end_condition;

	philo = (t_philo *)arg;
	end_condition = 0;
	while (!end_condition)
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philosopher(philo);
		think(philo);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->stop || philo->data->finished_count
			== philo->data->philo_count)
			end_condition = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	return (NULL);
}

void	*philosopher_routine_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	log_state(philo->data, philo->id, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	announce_death(philo->data, philo->id);
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->monitor_thread, NULL, monitor_routine, data);
	while (i < data->philo_count)
	{
		pthread_create(&data->philo[i].thread_id, NULL, philo_routine,
			&data->philo[i]);
		i++;
	}
	return (0);
}

int	create_single_thread(t_data *data)
{
	pthread_create(&data->philo[0].thread_id, NULL,
		philosopher_routine_single, &data->philo[0]);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitor_thread, NULL);
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}
