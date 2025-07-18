/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:48 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:45:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->finish_mutex, NULL);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philo[i].left_fork);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
}

void	init_philosopher_data(t_data *data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].last_meal_time = data->start_time;
	data->philo[i].meals_eaten = 0;
	data->philo[i].finished = 0;
	data->philo[i].data = data;
	data->philo[i].right_fork = NULL;
}

void	assign_right_fork(t_data *data, int i)
{
	if (i == data->philo_count - 1)
		data->philo[i].right_fork = &data->philo[0].left_fork;
	else
		data->philo[i].right_fork = &data->philo[i + 1].left_fork;
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->dead = 0;
	data->finished_count = 0;
	i = 0;
	while (i < data->philo_count)
	{
		init_philosopher_data(data, i);
		assign_right_fork(data, i);
		i++;
	}
	return (0);
}
