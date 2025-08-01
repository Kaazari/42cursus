/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	log_state(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	log_state(philo->data, philo->id, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time_eat_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->time_eat_mutex);
	log_state(philo->data, philo->id, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}
