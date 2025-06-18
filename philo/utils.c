#include "philo.h"

// void	create_threads(int nb, t_data *data)
// {
// 	int i = 0;
// 	pthread_t th[data->philo_nb];

// 	while (i++ < data->philo_nb)
// 	{
// 		if (pthread_create(th + i, NULL, &t_routine, NULL) != 0)
// 			return (1);
// 		printf("Thread %d has been created\n", i);
// 	}
// 	i = 0;
// 	while (i++ < data->philo_nb)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return (2);
// 			printf("thread %d finished exec\n", i);
// 	}
// }

// void	struct_define(char **av)
// {
// 	t_data data;

// 	data.philo_nb = av[1];
// 	if (data.philo_nb == 1)
// 	{
// 		printf("Number of philosophers is 2 minimum\n");
// 		exit(1);
// 	}
// 	data.fork = data.philo_nb;
// 	data.tt_die = av[2];
// 	data.tt_eat = av[3];
// 	data.tt_sleep = av[4];
// }

// void	eating(t_philo *philo)
// {
// 	t_data *data = philo->data;

// 	if (death_status(data))
// 		return ;
// 	pthread_mutex_lock(&data->fork[philo->l_fork]);
// 	printer(philo->id, "has taken a fork\n", data);
// 	if (death_status(data))
// 	{
// 		pthread_mutex_unlock(&data->fork[philo->l_fork]);
// 		return ;
// 	}
// 	pthread_mutex_lock(&data->fork[philo->r_fork]);
// 	if (death_status(data))
// 	{
// 		pthread_mutex_unlock(&data->fork[philo->l_fork]);
// 		pthread_mutex_unlock(&data->fork[philo->r_fork]);
// 		return ;
// 	}
// 	printer(philo->id, "has taken a fork\n", data);
// 	printer(philo->id, "is eating\n", data);
// 	pthread_mutex_lock(&data->meal);
// 	philo->last_meal = timeis();
// 	pthread_mutex_unlock(&data->meal);
// 	precise_sleep(data, data->tt_eat);
// 	if (death_status(data))
// 	{
// 		pthread_mutex_unlock(&data->fork[philo->l_fork]);
// 		pthread_mutex_unlock(&data->fork[philo->r_fork]);
// 		return ;
// 	}
// 	pthread_mutex_lock(&data->meal);
// 	philo->meals++;
// 	pthread_mutex_unlock(&data->meal);
// 	pthread_mutex_unlock(&data->fork[philo->l_fork]);
// 	pthread_mutex_unlock(&data->fork[philo->r_fork]);
// }
