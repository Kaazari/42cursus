/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_simulation(t_data *data)
{
	free(data->philo);
	free(data->forks);
	destroy_mutexes(data);
}

void	error_exit(t_data *data, char *message)
{
	cleanup_simulation(data);
	printf("Error: %s\n", message);
	exit(1);
}

int	handle_error(t_data *data, int error_code, char *message)
{
	(void)data;
	printf("Error: %s\n", message);
	return (error_code);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&data->time_eat_mutex);
}
