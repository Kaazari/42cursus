/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:53 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:46:44 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->data->time_eat_mutex);
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (!check_death(philo->data, 0) && !philo->finished
		&& ((get_time() - philo->last_meal_time)
			>= (long)philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->time_eat_mutex);
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->data->print_mutex);
		check_death(philo->data, 1);
	}
	pthread_mutex_unlock(&philo->data->time_eat_mutex);
	pthread_mutex_unlock(&philo->data->finish_mutex);
	return (NULL);
}
