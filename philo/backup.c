#include "philo.h"

// valgrind --tool=helgrind --fair-sched=yes

// remove ft_atoi put an ft ft_atoi
// funcheck
// ./philo 5 800 200 200
// ./philo 1 800 200 200
// ./philo 5 800 200 200 7
// ./philo int max ou -1
//

// contenu de mon .h

// #ifndef PHILO_H
// # define PHILO_H
// # define INT_MAX 2147483647
// # define INT_MIN -2147483648

// # include <unistd.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include <pthread.h>
// # include <string.h>
// # include <sys/time.h>

// typedef struct s_data
// {
// 	int					philo_nb;
// 	int					tt_eat;
// 	int					tt_die;
// 	int					tt_sleep;
// 	int					nb_meals;
// 	int					isdead;
// 	long long			timestamp_og;
// 	int					meal_ok;
// 	int					printer_ok;
// 	int					death_ok;
// 	pthread_mutex_t		meal;
// 	pthread_mutex_t		death;
// 	pthread_mutex_t		fork[200];
// 	pthread_mutex_t		printer;
// }				t_data;

// typedef struct s_philo
// {
// 	t_data				*data;
// 	int					id;
// 	int					meals;
// 	int					l_fork;
// 	int					r_fork;
// 	long long			last_meal;
// }				t_philo;

// void	*t_routine();
// void	create_threads(int nb, t_data *data);
// void	struct_define(char **av);

// #endif

long long	timeis(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	death_status(t_data *data)
{
	int status;

	pthread_mutex_lock(&data->death);
	status = data->isdead;
	pthread_mutex_unlock(&data->death);
	return (status);
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

void	printer(int id, char *msg, t_data *data)
{
	long long	timestamp;

	pthread_mutex_lock(&data->printer);
	if (!death_status(data))
	{
		timestamp = timeis() - data->timestamp_og;
		ft_putnbr_fd(timestamp, 1);
		write(1, " ", 1);
		ft_putnbr_fd(id + 1, 1);
		write(1, " ", 1);
		ft_putstr_fd(msg, 1);
	}
	pthread_mutex_unlock(&data->printer);
}


// 5 800 200 200

// void	precise_sleep(t_data *data)
// {
// 	struct timeval start, current;
// 	long	passed;

// 	gettimeofday(&start, NULL);
// 	while (1)
// 	{
// 		usleep(500);
// 		gettimeofday(&current, NULL);
// 		passed = (current.tv_sec - start.tv_sec) * 1000
// 				+ (current.tv_usec - start.tv_usec) / 1000;
// 		if (passed >= data->tt_sleep)
// 			break ;
// 	}
// }

int	ft_atoi(const char *str, int *result)
{
	long long	num = 0;
	int			sign = 1;
	int			i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	if (str[i] < '0' || str[i] > '9')
		return (0);

	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && num < INT_MIN))
			return (0);
		i++;
	}

	if (str[i] != '\0')
		return (0);
	if (sign == -1)
		return (0);

	*result = (int)(num * sign);
	return (1);
}


// void	printer(int id, char *s, t_data *data)
// {
// 	pthread_mutex_lock(&data->printer);
// 	if (!death_status(data))
// 	{
// 		printf("%lli %i %s", timeis() - data->timestamp_og, id + 1, s);
// 	}
// 	pthread_mutex_unlock(&data->printer);
// }

void	precise_sleep(t_data *data, int time)
{
	struct timeval start, current;
	long	passed;

	gettimeofday(&start, NULL);
	while (!death_status(data))
	{
		gettimeofday(&current, NULL);
		passed = (current.tv_sec - start.tv_sec) * 1000
		+ (current.tv_usec - start.tv_usec) / 1000;
		if (passed >= time)
			break ;
		usleep(100);
	}
}

void	moni_loop(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while(i != data->philo_nb && !death_status(data))
	{
		pthread_mutex_lock(&data->meal);
		if ((timeis() - philo[i].last_meal) > data->tt_die)
		{
			printer(philo[i].id, "\033[0;31mis dead\n", data);
			pthread_mutex_lock(&data->death);
			data->isdead = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_unlock(&data->meal);
			break ;
		}
		pthread_mutex_unlock(&data->meal);
		usleep(500);
		i++;
	}
}

void	*monitoring(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo[0].data;
	int	i;

	i = 0;
	while (i != data->philo_nb)
	{
		moni_loop(data, philo);
		if (death_status(data))
			break ;
		i = 0;
		while (data->nb_meals != -1 && i < data->philo_nb && philo[i].meals >= data->nb_meals)
			i++;
		if (i == data->philo_nb)
		{
			pthread_mutex_lock(&data->death);
			data->isdead = 1;
			pthread_mutex_unlock(&data->death);
			break ;
		}
	}
	return (NULL);
}

pthread_mutex_t	*min_mutex(pthread_mutex_t *a, pthread_mutex_t *b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

pthread_mutex_t	*max_mutex(pthread_mutex_t *a, pthread_mutex_t *b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	sleep_think(t_philo *philo)
{
	t_data *data = philo->data;

	pthread_mutex_lock(&data->meal);
	philo->last_meal = timeis();
	pthread_mutex_unlock(&data->meal);
	precise_sleep(data, data->tt_eat);
	pthread_mutex_lock(&data->meal);
	philo->meals++;
	pthread_mutex_unlock(&data->meal);
}

// void	eating(t_philo *philo)
// {
// 	t_data *data = philo->data;

// 	pthread_mutex_lock(min_mutex(&data->fork[philo->l_fork], &data->fork[philo->r_fork]));
// 	printer(philo->id, "has taken a fork\n", data);
// 	pthread_mutex_lock(max_mutex(&data->fork[philo->l_fork], &data->fork[philo->r_fork]));
// 	printer(philo->id, "has taken a fork\n", data);
// 	printer(philo->id, "is eating\n", data);
// 	sleep_think(philo);
// 	pthread_mutex_unlock(&data->fork[philo->l_fork]);
// 	pthread_mutex_unlock(&data->fork[philo->r_fork]);
// }

void eating(t_philo *philo)
{
	t_data *data = philo->data;
	pthread_mutex_t *first_mutex;
	pthread_mutex_t *second_mutex;

	first_mutex = min_mutex(&data->fork[philo->l_fork], &data->fork[philo->r_fork]);
	second_mutex = max_mutex(&data->fork[philo->l_fork], &data->fork[philo->r_fork]);

	pthread_mutex_lock(first_mutex);
	if (death_status(data))
	{
		pthread_mutex_unlock(first_mutex);
		return;
	}
	printer(philo->id, "has taken a fork\n", data);

	pthread_mutex_lock(second_mutex);
	if (death_status(data))
	{
		pthread_mutex_unlock(second_mutex);
		pthread_mutex_unlock(first_mutex);
		return;
	}
	printer(philo->id, "has taken a fork\n", data);

	if (death_status(data))
	{
		pthread_mutex_unlock(second_mutex);
		pthread_mutex_unlock(first_mutex);
		return;
	}
	printer(philo->id, "is eating\n", data);

	pthread_mutex_lock(&data->meal);
	philo->last_meal = timeis();
	pthread_mutex_unlock(&data->meal);

	precise_sleep(data, data->tt_eat);

	pthread_mutex_lock(&data->meal);
	philo->meals++;
	pthread_mutex_unlock(&data->meal);

	pthread_mutex_unlock(second_mutex);
	pthread_mutex_unlock(first_mutex);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	printer(philo->id, "has taken a fork\n", philo->data);
	while (!death_status(philo->data))
	{
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
}

void	*t_routine(void *arg)
{
	t_philo *philo = (t_philo*) arg;
	if (philo->id % 2)
		usleep(10000);
	if (philo->data->philo_nb == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		if ((philo->data->nb_meals != -1 && philo->meals >= philo->data->nb_meals)
			|| death_status(philo->data))
			break ;
		eating(philo);
		if (death_status(philo->data))
			break ;
		printer(philo->id, "is sleeping\n", philo->data);
		if (death_status(philo->data))
			break ;
		precise_sleep(philo->data, philo->data->tt_sleep);
		if (death_status(philo->data))
			break ;
		printer(philo->id, "is thinking\n", philo->data);
	}
	return (NULL);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL) != 0)
		return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->printer), NULL) != 0)
		data->printer_ok = 1;
	if (pthread_mutex_init(&(data->meal), NULL) != 0)
	data->meal_ok = 1;
	if (pthread_mutex_init(&(data->death), NULL) != 0)
	data->death_ok = 1;
	return (0);
}

void	issue(t_data *data, t_philo *philo, pthread_t *th)
{
	int i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	if (data->printer_ok)
		pthread_mutex_destroy(&data->printer);
	if (data->meal_ok)
		pthread_mutex_destroy(&data->meal);
	if (data->death_ok)
		pthread_mutex_destroy(&data->death);
	if (th)
		free(th);
	if (philo)
	free(philo);
	if (data)
	free(data);
}

int	init_philo(t_philo *philo, t_data *data, pthread_t *th)
{
	int i = 0;

	while (i < data->philo_nb)
	{
		memset(&philo[i], 0, sizeof *philo);
		philo[i].data = data;
		philo[i].id = i;
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % data->philo_nb;
		philo[i].last_meal = timeis();
		if (pthread_create(th + i, NULL, &t_routine, (void*) &philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	if (!ft_atoi(av[1], &data->philo_nb)
		|| !ft_atoi(av[2], &data->tt_die)
		|| !ft_atoi(av[3], &data->tt_eat)
		|| !ft_atoi(av[4], &data->tt_sleep))
	{
		printf("invalid arguments.\n");
		return (1);
	}
	if (av[5])
	{
		if (!ft_atoi(av[5], &data->nb_meals)
			|| data->nb_meals <= 0)
			return (1);
	}
	else
		data->nb_meals = -1;
	return (0);
}

int	main(int ac, char **av)
{
	// init

	if (ac != 5 && ac != 6)
	{
		printf("not enough arguments.\n");
		return (0);
	}

	t_data	*data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	memset(data, 0, sizeof(t_data));

	if(init_data(data, av))
		return (1);


	if (init_mutexes(data))
		return (1);

	t_philo *philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!philo)
		return (1);
	pthread_t *th = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!th)
		return (1);

	data->timestamp_og = timeis();
	if (init_philo(philo, data, th))
		return (1);

	pthread_t moni;
	if (pthread_create(&moni, NULL, &monitoring, (void *)philo) != 0)
		return (1);

	int	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		i++;
	}
	pthread_join(moni, NULL);
	issue(data, philo, th);
	return (0);
}
