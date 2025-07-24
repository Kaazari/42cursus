/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	determine_fork_order(t_philo *philo, pthread_mutex_t **first,
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

void	take_first_fork(t_philo *philo, pthread_mutex_t *first_fork)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_second_fork(t_philo *philo, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	eat_and_update_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("is eating\n", philo);
	pthread_mutex_lock(&philo->data->time_eat_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->time_eat_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat);
}
