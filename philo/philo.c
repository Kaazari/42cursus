#include "philo.h"

long long	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

int	ft_atoi_safe(const char *str)
{
	long long	result = 0;
	int			i = 0;

	// Skip whitespace
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	// Check sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}

	// Must have at least one digit
	if (str[i] < '0' || str[i] > '9')
		return (-1);

	// Parse digits
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}

	// Must be end of string
	if (str[i] != '\0')
		return (-1);

	return ((int)result);
}

void	precise_usleep(long long time_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_ms)
		usleep(time_ms / 10);
}

int	check_death(t_data *data, int set_death)
{
	int status;

	pthread_mutex_lock(&data->death_mutex);
	if (set_death)
		data->someone_died = set_death;
	status = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}

void	write_status(char *str, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		time = get_time() - philo->data->start_time;
		ft_putnbr_fd(time, 1);
		write(1, " ", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		ft_putstr_fd(str, 1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	precise_usleep(philo->data->time_to_die + 1);

	pthread_mutex_lock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->finish_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);

	if (!philo->data->someone_died && !philo->finished &&
		((get_time() - philo->last_meal_time) >= (long)(philo->data->time_to_die)))
	{
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->finish_mutex);

		pthread_mutex_lock(&philo->data->print_mutex);
		ft_putnbr_fd(get_time() - philo->data->start_time, 1);
		write(1, " ", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		ft_putstr_fd("died\n", 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->finish_mutex);
	}
	return (NULL);
}

void	sleep_think(t_philo *philo)
{
	write_status("is sleeping\n", philo);
	precise_usleep(philo->data->time_to_sleep);
	write_status("is thinking\n", philo);
}

void	eat_activity(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	// Pour les gros nombres, alterner l'ordre selon la parité
	if (philo->data->philo_count > 100)
	{
		if (philo->id % 2 == 1)
		{
			first_fork = philo->right_fork;
			second_fork = &philo->left_fork;
		}
		else
		{
			first_fork = &philo->left_fork;
			second_fork = philo->right_fork;
		}
	}
	else
	{
		// Ordre classique pour les petits nombres
		if (&philo->left_fork < philo->right_fork)
		{
			first_fork = &philo->left_fork;
			second_fork = philo->right_fork;
		}
		else
		{
			first_fork = philo->right_fork;
			second_fork = &philo->left_fork;
		}
	}

	pthread_mutex_lock(first_fork);
	write_status("has taken a fork\n", philo);

	if (!philo->right_fork)
	{
		precise_usleep(philo->data->time_to_die * 2);
		pthread_mutex_unlock(first_fork);
		return ;
	}

	pthread_mutex_lock(second_fork);
	write_status("has taken a fork\n", philo);
	write_status("is eating\n", philo);

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);

	precise_usleep(philo->data->time_to_eat);

	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);

	sleep_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	// Décalage réduit pour les gros nombres
	if (philo->data->philo_count > 100)
		usleep((philo->id % 20) * 100);  // Max 2ms au lieu de 10ms
	else if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 10);

	while (!check_death(philo->data, 0))
	{
		pthread_create(&philo->death_thread, NULL, death_monitor, arg);
		eat_activity(philo);
		pthread_detach(philo->death_thread);

		if (philo->data->must_eat_count != -1 &&
			(int)++philo->meals_eaten == philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->data->finish_mutex);
			philo->finished = 1;
			philo->data->finished_count++;
			if (philo->data->finished_count == philo->data->philo_count)
			{
				pthread_mutex_unlock(&philo->data->finish_mutex);
				check_death(philo->data, 2);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->finish_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->finish_mutex, NULL);

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->philos[i].left_fork, NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}

	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->finish_mutex);

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->someone_died = 0;
	data->finished_count = 0;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].finished = 0;
		data->philos[i].data = data;
		data->philos[i].right_fork = NULL;

		if (data->philo_count == 1)
		{
			i++;
			continue;
		}

		if (i == data->philo_count - 1)
			data->philos[i].right_fork = &data->philos[0].left_fork;
		else
			data->philos[i].right_fork = &data->philos[i + 1].left_fork;
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->threads[i], NULL, philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	wait_for_completion(t_data *data)
{
	int	i;

	while (!check_death(data, 0))
		precise_usleep(1);

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}

	if (data->someone_died == 2 && data->must_eat_count != -1)
	{
		printf("Each philosopher ate %d time(s)\n", data->must_eat_count);
	}

	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	data->philo_count = ft_atoi_safe(argv[1]);
	data->time_to_die = ft_atoi_safe(argv[2]);
	data->time_to_eat = ft_atoi_safe(argv[3]);
	data->time_to_sleep = ft_atoi_safe(argv[4]);

	if (data->philo_count <= 0 || data->time_to_die <= 0 ||
		data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}

	if (argc == 6)
	{
		data->must_eat_count = ft_atoi_safe(argv[5]);
		if (data->must_eat_count <= 0)
		{
			printf("Error: number_of_times_each_philosopher_must_eat must be a positive integer\n");
			return (1);
		}
	}
	else
		data->must_eat_count = -1;

	return (0);
}

int	allocate_memory(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (1);

	data->threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->threads)
	{
		free(data->philos);
		return (1);
	}

	return (0);
}

void	cleanup(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));

	if (parse_arguments(argc, argv, &data))
		return (1);

	if (allocate_memory(&data))
		return (1);

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
