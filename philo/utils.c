/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:07 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:08 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr_fd(long long n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

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

int	check_death(t_data *data, int set_death)
{
	int	status;

	pthread_mutex_lock(&data->death_mutex);
	if (set_death)
		data->dead = set_death;
	status = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}
