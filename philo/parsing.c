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

int	parse_number(char *str, int *i)
{
	long long	result;

	result = 0;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		if (result > INT_MAX)
			return (-1);
		(*i)++;
	}
	return ((int)result);
}

int	ft_atoi_safe(char *str)
{
	int	i;
	int	result;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	result = parse_number(str, &i);
	if (result == -1 || str[i] != '\0')
		return (-1);
	return (result);
}

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
