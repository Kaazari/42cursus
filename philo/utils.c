/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:58:17 by zdjitte           #+#    #+#             */
/*   Updated: 2025/08/04 22:58:18 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	left_fork(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	right_fork(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	atoi_strict(char *s)
{
	int	sign;
	int	res;

	sign = 0;
	res = 0;
	while ((s[sign] >= 9 && s[sign] <= 13) || s[sign] == 32)
		sign++;
	if (s[sign] == '-')
		return (-1);
	if (s[sign] == '+')
		sign++;
	while (s[sign] >= '0' && s[sign] <= '9')
	{
		res = res * 10 + (s[sign] - 48);
		sign++;
	}
	return (res);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	print_error(void)
{
	printf("Please enter: [nb_philos] [time_to_die] [time_to_eat] \
		[time_to_sleep] [meals_to_eat](last one is an option).\n");
	return (0);
}
