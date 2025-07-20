/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 04:21:07 by zdjitte           #+#    #+#             */
/*   Updated: 2025/01/17 04:21:07 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_thread;

	philo = (t_philo *)arg;

	// Délai initial pour les philosophes pairs comme Amy
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 10);

	while (!check_death(philo->data, 0))
	{
		// Créer un thread de mort à chaque cycle comme Amy
		pthread_create(&death_thread, NULL, death_monitor, philo);

		// Exécuter les actions du philosophe
		eat_activity(philo);

		// Détacher le thread de mort
		pthread_detach(death_thread);

		// Vérifier si le philosophe a mangé suffisamment
		if (philo->data->must_eat_count != -1
			&& ++philo->meals_eaten == philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->data->finish_mutex);
			philo->finished = 1;
			philo->data->finished_count++;
			if (philo->data->finished_count == philo->data->philo_count)
			{
				pthread_mutex_unlock(&philo->data->finish_mutex);
				check_death(philo->data, 2);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->finish_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
