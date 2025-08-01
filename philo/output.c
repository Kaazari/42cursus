/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *philo)
{
	long int	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo->data, 0))
		printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	log_state(t_data *data, int philo_id, char *message)
{
	long int	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->stop)
		printf("%ld %d %s\n", timestamp, philo_id, message);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}

void	announce_death(t_data *data, int philo_id)
{
	long int	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->death_mutex);
	data->stop = 1;
	printf("%ld %d died\n", timestamp, philo_id);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}

void	announce_finish(t_data *data)
{
	long int	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld All philosophers have eaten %d times\n", timestamp,
		data->must_eat_count);
	pthread_mutex_unlock(&data->print_mutex);
}
