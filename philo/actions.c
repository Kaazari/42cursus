/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:43 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:45:14 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_philo *philo)
{
	write_status("is sleeping\n", philo);
	precise_usleep(philo->data->time_to_sleep);
	write_status("is thinking\n", philo);
}

void	get_fork_order(t_philo *philo, pthread_mutex_t **first,
	pthread_mutex_t **second)
{
	if (&philo->left_fork < philo->right_fork)
	{
		*first = &philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = &philo->left_fork;
	}
}

void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	write_status("has taken a fork\n", philo);
	precise_usleep(philo->data->time_to_die * 2);
	pthread_mutex_unlock(&philo->left_fork);
}

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_usleep(philo->data->time_to_eat);
}

void	eat_activity(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->data->philo_count == 1)
	{
		handle_single_philosopher(philo);
		return ;
	}
	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	write_status("has taken a fork\n", philo);
	pthread_mutex_lock(second_fork);
	write_status("has taken a fork\n", philo);
	write_status("is eating\n", philo);
	eating_process(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	sleep_think(philo);
}
