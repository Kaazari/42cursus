/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:58 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:25:59 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arguments(t_data *data)
{
	if (data->philo_count <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	return (0);
}

int	parse_optional_argument(int argc, char **argv, t_data *data)
{
	if (argc == 6)
	{
		data->must_eat_count = ft_atoi_safe(argv[5]);
		if (data->must_eat_count <= 0)
		{
			printf("Error: number_of_times_each_philosopher_must_eat"
				"must be a positive integer\n");
			return (1);
		}
	}
	else
		data->must_eat_count = -1;
	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat"
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data->philo_count = ft_atoi_safe(argv[1]);
	data->time_to_die = ft_atoi_safe(argv[2]);
	data->time_to_eat = ft_atoi_safe(argv[3]);
	data->time_to_sleep = ft_atoi_safe(argv[4]);
	if (validate_arguments(data))
		return (1);
	return (parse_optional_argument(argc, argv, data));
}

int	allocate_memory(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
		return (1);
	data->threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->threads)
	{
		free(data->philo);
		return (1);
	}
	return (0);
}

void	cleanup(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->threads)
		free(data->threads);
}
