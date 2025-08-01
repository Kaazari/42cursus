/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_strict(const char *str, int *result)
{
	if (!str || !result)
		return (-1);
	*result = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (handle_error(data, -1, "Invalid number of arguments"));
	if (atoi_strict(argv[1], &data->philo_count) != 0)
		return (handle_error(data, -1, "Invalid number of philosophers"));
	if (atoi_strict(argv[2], &data->time_to_die) != 0)
		return (handle_error(data, -1, "Invalid time to die"));
	if (atoi_strict(argv[3], &data->time_to_eat) != 0)
		return (handle_error(data, -1, "Invalid time to eat"));
	if (atoi_strict(argv[4], &data->time_to_sleep) != 0)
		return (handle_error(data, -1, "Invalid time to sleep"));
	if (argc == 6 && atoi_strict(argv[5], &data->must_eat_count) > -1)
		data->must_eat_count = data->must_eat_count;
	else if (argc == 6 && atoi_strict(argv[5], &data->must_eat_count) == -1)
		return (handle_error(data, -1, "Invalid number of meals"));
	else
		data->must_eat_count = -1;
	if (data->philo_count <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (handle_error(data, -1, "Invalid argument values"));
	if (data->must_eat_count != -1 && data->must_eat_count <= 0)
		return (handle_error(data, -1, "Invalid number of meals"));
	return (0);
}
