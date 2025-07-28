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
	if (check_death(philo->data, 0))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_sleep);
	if (check_death(philo->data, 0))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (check_death(philo->data, 0))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_die * 2);
	pthread_mutex_unlock(&philo->left_fork);
}

static void	handle_eating_process(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	take_second_fork(philo, second_fork);
	if (check_death(philo->data, 0))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	eat_and_update_time(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	determine_fork_order(philo, &first_fork, &second_fork);
	take_first_fork(philo, first_fork);
	if (check_death(philo->data, 0))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	if (!philo->right_fork)
	{
		ft_usleep(philo->data->time_to_die * 2);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	handle_eating_process(philo, first_fork, second_fork);
}

void	eat_activity(t_philo *philo)
{
	if (check_death(philo->data, 0))
		return ;
	if (philo->data->philo_count == 1)
	{
		handle_single_philosopher(philo);
		return ;
	}
	take_forks_and_eat(philo);
	if (check_death(philo->data, 0))
		return ;
	sleep_think(philo);
}
