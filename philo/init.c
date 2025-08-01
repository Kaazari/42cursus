/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->start_time = get_time();
	data->stop = 0;
	data->finished_count = 0;
}

int	allocate_memory(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
		return (1);
	return (0);
}

void	cleanup(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->finish_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->time_eat_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].finished = 0;
		data->philo[i].last_meal_time = get_time();
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_count;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}
