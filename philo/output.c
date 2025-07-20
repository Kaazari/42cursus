/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:55 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:25:56 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *philo)
{
	long int	time;

	time = get_time() - philo->data->start_time;
	if (time >= 0 && time <= 2147483647 && !check_death(philo->data, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", philo->id, str);
	}
}
