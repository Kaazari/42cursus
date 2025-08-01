/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals_completed(t_philo *philo)
{
	if (philo->data->must_eat_count != -1
		&& philo->meals_eaten >= philo->data->must_eat_count)
	{
		pthread_mutex_lock(&philo->data->finish_mutex);
		if (!philo->finished)
		{
			philo->finished = 1;
			philo->data->finished_count++;
		}
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data) < 0)
		return (1);
	init_simulation(&data);
	if (init_philosophers(&data) || init_mutexes(&data))
		return (1);
	if (data.philo_count == 1)
	{
		create_single_thread(&data);
		pthread_join(data.philo[0].thread_id, NULL);
		cleanup_simulation(&data);
		return (0);
	}
	create_threads(&data);
	join_threads(&data);
	cleanup_simulation(&data);
	return (0);
}
