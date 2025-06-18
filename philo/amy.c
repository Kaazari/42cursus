// #ifndef PHILO_H
// # define PHILO_H

// /*
// ** libraries
// */

// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <sys/time.h>
// # include <pthread.h>

// /*
// ** structures
// */

// typedef struct s_arg
// {
// 	int						total;
// 	int						die;
// 	int						eat;
// 	int						sleep;
// 	int						m_eat;
// 	long int				start_t;
// 	pthread_mutex_t			write_mutex;
// 	pthread_mutex_t			dead;
// 	pthread_mutex_t			time_eat;
// 	pthread_mutex_t			finish;
// 	int						nb_p_finish;
// 	int						stop;
// }							t_arg;

// typedef struct s_philo
// {
// 	int						id;
// 	pthread_t				thread_id;
// 	pthread_t				thread_death_id;
// 	pthread_mutex_t			*r_f;
// 	pthread_mutex_t			l_f;
// 	t_arg					*pa;
// 	long int				ms_eat;
// 	unsigned int			nb_eat;
// 	int						finish;
// }							t_philo;

// typedef struct s_p
// {
// 	t_philo					*ph;
// 	t_arg					a;
// }							t_p;

// /*
// ** functions
// */

// int				parse_args(int argc, char **argv, t_p *p);
// int				initialize(t_p *p);
// int				ft_exit(char *str);
// void			write_status(char *str, t_philo *ph);
// long int		actual_time(void);
// void			ft_putstr_fd(char *s, int fd);
// void			ft_usleep(long int time_in_ms);
// int				threading(t_p *p);
// void			activity(t_philo *ph);
// int				check_death(t_philo *ph, int i);
// int				ft_strlen(char *str);

// #endif

// void	ft_putchar_fd(char c, int fd)
// {
// 	if (fd >= 0)
// 		write(fd, &c, 1);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (fd >= 0)
// 	{
// 		while (s && *s)
// 		{
// 			write(fd, &*s, 1);
// 			s++;
// 		}
// 	}
// }

// void	ft_putnbr_fd(long int ln, int fd)
// {
// 	if (ln < 0)
// 	{
// 		ln *= -1;
// 		ft_putchar_fd('-', fd);
// 	}
// 	if (ln >= 10)
// 	{
// 		ft_putnbr_fd(ln / 10, fd);
// 		ft_putnbr_fd(ln % 10, fd);
// 	}
// 	else
// 	{
// 		if (fd >= 0)
// 			ft_putchar_fd(ln + 48, fd);
// 	}
// }

// int	ft_strlen(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int	check_death(t_philo *ph, int i)
// {
// 	pthread_mutex_lock(&ph->pa->dead);
// 	if (i)
// 		ph->pa->stop = i;
// 	if (ph->pa->stop)
// 	{
// 		pthread_mutex_unlock(&ph->pa->dead);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&ph->pa->dead);
// 	return (0);
// }

// long int	actual_time(void)
// {
// 	long int			time;
// 	struct timeval		current_time;

// 	time = 0;
// 	if (gettimeofday(&current_time, NULL) == -1)
// 		ft_exit("Gettimeofday returned -1\n");
// 	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
// 	return (time);
// }

// void	ft_usleep(long int time_in_ms)
// {
// 	long int	start_time;

// 	start_time = 0;
// 	start_time = actual_time();
// 	while ((actual_time() - start_time) < time_in_ms)
// 		usleep(time_in_ms / 10);
// }

// void	write_status(char *str, t_philo *ph)
// {
// 	long int		time;

// 	time = -1;
// 	time = actual_time() - ph->pa->start_t;
// 	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
// 	{
// 		printf("%ld ", time);
// 		printf("Philo %d %s", ph->id, str);
// 	}
// }

// void	sleep_think(t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->pa->write_mutex);
// 	write_status("is sleeping\n", ph);
// 	pthread_mutex_unlock(&ph->pa->write_mutex);
// 	ft_usleep(ph->pa->sleep);
// 	pthread_mutex_lock(&ph->pa->write_mutex);
// 	write_status("is thinking\n", ph);
// 	pthread_mutex_unlock(&ph->pa->write_mutex);
// }

// void	activity(t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->l_f);
// 	pthread_mutex_lock(&ph->pa->write_mutex);
// 	write_status("has taken a fork\n", ph);
// 	pthread_mutex_unlock(&ph->pa->write_mutex);
// 	if (!ph->r_f)
// 	{
// 		ft_usleep(ph->pa->die * 2);
// 		return ;
// 	}
// 	pthread_mutex_lock(ph->r_f);
// 	pthread_mutex_lock(&ph->pa->write_mutex);
// 	write_status("has taken a fork\n", ph);
// 	pthread_mutex_unlock(&ph->pa->write_mutex);
// 	pthread_mutex_lock(&ph->pa->write_mutex);
// 	write_status("is eating\n", ph);
// 	pthread_mutex_lock(&ph->pa->time_eat);
// 	ph->ms_eat = actual_time();
// 	pthread_mutex_unlock(&ph->pa->time_eat);
// 	pthread_mutex_unlock(&ph->pa->write_mutex);
// 	ft_usleep(ph->pa->eat);
// 	pthread_mutex_unlock(ph->r_f);
// 	pthread_mutex_unlock(&ph->l_f);
// 	sleep_think(ph);
// }

// void	*is_dead(void	*data)
// {
// 	t_philo					*ph;

// 	ph = (t_philo *)data;
// 	ft_usleep(ph->pa->die + 1);
// 	pthread_mutex_lock(&ph->pa->time_eat);
// 	pthread_mutex_lock(&ph->pa->finish);
// 	if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
// 		>= (long)(ph->pa->die)))
// 	{
// 		pthread_mutex_unlock(&ph->pa->time_eat);
// 		pthread_mutex_unlock(&ph->pa->finish);
// 		pthread_mutex_lock(&ph->pa->write_mutex);
// 		write_status("died\n", ph);
// 		pthread_mutex_unlock(&ph->pa->write_mutex);
// 		check_death(ph, 1);
// 	}
// 	pthread_mutex_unlock(&ph->pa->time_eat);
// 	pthread_mutex_unlock(&ph->pa->finish);
// 	return (NULL);
// }

// void	*thread(void *data)
// {
// 	t_philo					*ph;

// 	ph = (t_philo *)data;
// 	if (ph->id % 2 == 0)
// 		ft_usleep(ph->pa->eat / 10);
// 	while (!check_death(ph, 0))
// 	{
// 		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
// 		activity(ph);
// 		pthread_detach(ph->thread_death_id);
// 		if ((int)++ph->nb_eat == ph->pa->m_eat)
// 		{
// 			pthread_mutex_lock(&ph->pa->finish);
// 			ph->finish = 1;
// 			ph->pa->nb_p_finish++;
// 			if (ph->pa->nb_p_finish == ph->pa->total)
// 			{
// 				pthread_mutex_unlock(&ph->pa->finish);
// 				check_death(ph, 2);
// 			}
// 			pthread_mutex_unlock(&ph->pa->finish);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }

// int	threading(t_p *p)
// {
// 	int	i;

// 	i = 0;
// 	while (i < p->a.total)
// 	{
// 		p->ph[i].pa = &p->a;
// 		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
// 			return (ft_exit("Pthread did not return 0\n"));
// 		i++;
// 	}
// 	return (1);
// }


// int	ft_atoi(const char *str)
// {
// 	int		i;
// 	long	sum;

// 	sum = 0;
// 	i = -1;
// 	while (str[++i])
// 		sum = (sum * 10) + (str[i] - 48);
// 	return (sum);
// }

// int	numeric(char **argv, int i, int j)
// {
// 	while (argv[j])
// 	{
// 		while (argv[j][i])
// 		{
// 			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
// 				return (0);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 	}
// 	return (1);
// }

// int	parse_args(int argc, char **argv, t_p *p)
// {
// 	if ((argc == 5 || argc == 6) && numeric(argv, 0, 1))
// 	{
// 		p->a.total = ft_atoi(argv[1]);
// 		p->a.die = ft_atoi(argv[2]);
// 		p->a.eat = ft_atoi(argv[3]);
// 		p->a.sleep = ft_atoi(argv[4]);
// 		p->a.m_eat = -1;
// 		if (argc == 6)
// 			p->a.m_eat = ft_atoi(argv[5]);
// 		if (p->a.total <= 0 || p->a.die <= 0 || p->a.eat <= 0 \
// 			|| p->a.sleep <= 0)
// 			return (0);
// 		return (1);
// 	}
// 	return (0);
// }

// void	init_mutex(t_p *p)
// {
// 	pthread_mutex_init(&p->a.write_mutex, NULL);
// 	pthread_mutex_init(&p->a.dead, NULL);
// 	pthread_mutex_init(&p->a.time_eat, NULL);
// 	pthread_mutex_init(&p->a.finish, NULL);
// }

// int	initialize(t_p *p)
// {
// 	int	i;

// 	i = 0;
// 	p->a.start_t = actual_time();
// 	p->a.stop = 0;
// 	p->a.nb_p_finish = 0;
// 	init_mutex(p);
// 	while (i < p->a.total)
// 	{
// 		p->ph[i].id = i + 1;
// 		p->ph[i].ms_eat = p->a.start_t;
// 		p->ph[i].nb_eat = 0;
// 		p->ph[i].finish = 0;
// 		p->ph[i].r_f = NULL;
// 		pthread_mutex_init(&p->ph[i].l_f, NULL);
// 		if (p->a.total == 1)
// 			return (1);
// 		if (i == p->a.total - 1)
// 			p->ph[i].r_f = &p->ph[0].l_f;
// 		else
// 			p->ph[i].r_f = &p->ph[i + 1].l_f;
// 		i++;
// 	}
// 	return (1);
// }


// int	ft_exit(char *str)
// {
// 	ft_putstr_fd("Error : ", 2);
// 	ft_putstr_fd(str, 2);
// 	return (0);
// }

// int	check_death2(t_p *p)
// {
// 	pthread_mutex_lock(&p->a.dead);
// 	if (p->a.stop)
// 	{
// 		pthread_mutex_unlock(&p->a.dead);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&p->a.dead);
// 	return (0);
// }

// void	stop(t_p *p)
// {
// 	int	i;

// 	i = -1;
// 	while (!check_death2(p))
// 		ft_usleep(1);
// 	while (++i < p->a.total)
// 		pthread_join(p->ph[i].thread_id, NULL);
// 	pthread_mutex_destroy(&p->a.write_mutex);
// 	i = -1;
// 	while (++i < p->a.total)
// 		pthread_mutex_destroy(&p->ph[i].l_f);
// 	if (p->a.stop == 2)
// 		printf("Each philosopher ate %d time(s)\n", p->a.m_eat);
// 	free(p->ph);
// }

// int	main(int argc, char **argv)
// {
// 	t_p		p;

// 	if (!(parse_args(argc, argv, &p)))
// 		return (ft_exit("Invalid Arguments\n"));
// 	p.ph = malloc(sizeof(t_philo) * p.a.total);
// 	if (!p.ph)
// 		return (ft_exit("Malloc returned NULL\n"));
// 	if (!initialize(&p) || !threading(&p))
// 	{
// 		free(p.ph);
// 		return (0);
// 	}
// 	stop(&p);
// }
