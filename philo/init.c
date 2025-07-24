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
}

int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->finish_mutex, NULL);
	pthread_mutex_init(&data->time_eat_mutex, NULL);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	ft_usleep(100);
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		write(2, "Error: failed to destroy print_mutex\n", 35);
	if (pthread_mutex_destroy(&data->death_mutex) != 0)
		write(2, "Error: failed to destroy death_mutex\n", 35);
	if (pthread_mutex_destroy(&data->finish_mutex) != 0)
		write(2, "Error: failed to destroy finish_mutex\n", 36);
	if (pthread_mutex_destroy(&data->time_eat_mutex) != 0)
		write(2, "Error: failed to destroy time_eat_mutex\n", 38);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_destroy(&data->philo[i].left_fork) != 0)
			write(2, "Error: failed to destroy fork mutex\n", 34);
		i++;
	}
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = data->start_time;
		data->philo[i].meals_eaten = 0;
		data->philo[i].finished = 0;
		data->philo[i].data = data;
		data->philo[i].right_fork = NULL;
		if (data->philo_count == 1)
			return (0);
		if (i == data->philo_count - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
	return (0);
}
