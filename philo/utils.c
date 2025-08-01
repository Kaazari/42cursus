/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_putnbr_fd(long int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_usleep(long int time_ms)
{
	long int	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_ms)
		usleep(100);
}

int	check_death(t_data *data, int set_death)
{
	pthread_mutex_lock(&data->death_mutex);
	if (set_death == 1)
		data->stop = 1;
	if (set_death == 2)
		data->stop = 2;
	if (data->stop)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}
