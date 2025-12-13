/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:58:28 by zdjitte           #+#    #+#             */
/*   Updated: 2025/08/04 22:58:29 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_start(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->philo_count % 2 == 0)
		i = 0;
	else
		i = 1;
	if (philo->id % 2 == 0 && i == 0)
		usleep(100);
	if (philo->id % 2 == 1 && i == 1)
		usleep(100);
	return ;
}

void	*start_routine(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->time_start = get_time();
	while (i < philo->data->philo_count)
	{
		sync_start(&philo[i]);
		pthread_create(&philo[i].thread_id, NULL, routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&philo->data->death_monitor,
		NULL, death_monitor, (void *)philo);
	while (i < philo->data->philo_count)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(philo->data->death_monitor, NULL);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->last_meal_time == 0)
		philo->last_meal_time = get_time();
	while (!death_status(philo->data) || !philo->data->all_eat)
	{
		eat(philo);
		if (philo->data->all_eat || death_status(philo->data))
			break ;
		time_to_sleep(philo);
		if (philo->data->all_eat || death_status(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}

static int	init_all(int ac, char **av, t_data *data, t_philo *philo)
{
	init_data_struct(ac, av, data);
	if (init_philo(philo, data))
	{
		free(data);
		free(philo);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!check_args(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * (atoi_strict(av[1]) + 1));
	if (!philo)
	{
		free(data);
		return (1);
	}
	if (init_all(ac, av, data, philo))
		return (1);
	if (data->philo_count > 1)
	{
		start_routine(philo);
		usleep(10000);
		cleanup_all(philo);
	}
	else if (data->philo_count == 1)
		one_philo(philo);
	return (0);
}
