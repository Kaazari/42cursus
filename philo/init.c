#include "philo.h"

void	init_data_struct(int ac, char **av, t_data *data)
{
	data->philo_count = atoi_strict(av[1]);
	data->time_to_die = atoi_strict(av[2]);
	data->time_to_eat = atoi_strict(av[3]);
	data->time_to_sleep = atoi_strict(av[4]);
	if (ac == 6)
		data->must_eat_count = atoi_strict(av[5]);
	else
		data->must_eat_count = 0;
	data->start_flag = 1;
	data->all_eat = 0;
	return ;
}

void	init_philo(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	init_mutexes(data);
	data->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * (data->philo_count + 1));
	while (i < data->philo_count)
	{
		philo[i].data = &data[0];
		philo[i].left_fork = i;
		if (i == data->philo_count - 1)
			philo[i].right_fork = 0;
		else
			philo[i].right_fork = i + 1;
		pthread_mutex_init(&data->forks[i], NULL);
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = 0;
		i++;
	}
	i = 0;
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_lock(&data->death_mutex);
	data->dead = 0 ;
	pthread_mutex_unlock(&data->death_mutex);
}

void	one_philo(t_philo *philo)
{
	printf("0 Philo 1 is thinking...\n");
	printf("0 Philo 1 has taken a fork.\n");
	printf("%d Philo 1 died.\n", philo->data->time_to_die);
	cleanup_all(philo);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (print_error());
	while (i < ac)
	{
		if (atoi_strict(av[i]) >= 0 && ft_isdigit(av[i]))
			i++;
		else
			return (print_error());
		if (atoi_strict(av[1]) == 0)
			return (print_error());
		if (av[5])
		{
			if (atoi_strict(av[5]) == 0)
				return (print_error());
		}
	}
	return (1);
}
