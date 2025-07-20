/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:50 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:25:51 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, philo_routine,
				&data->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	wait_for_completion(t_data *data)
{
	int	i;

	while (!check_death(data, 0))
		ft_usleep(1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	if (data->stop == 2 && data->must_eat_count != -1)
		printf("Each philosopher ate %d time(s)\n", data->must_eat_count);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_arguments(argc, argv, &data))
		return (1);
	if (allocate_memory(&data))
		return (1);
	data.start_time = get_time();
	data.stop = 0;
	data.finished_count = 0;
	if (init_mutexes(&data) || init_philosophers(&data))
	{
		cleanup(&data);
		return (1);
	}
	if (create_threads(&data))
	{
		destroy_mutexes(&data);
		cleanup(&data);
		return (1);
	}
	wait_for_completion(&data);
	destroy_mutexes(&data);
	cleanup(&data);
	return (0);
}
