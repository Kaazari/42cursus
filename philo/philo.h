#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		death_monitor;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	int				start_flag;
	int				philo_count;
	int				must_eat_count;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				stop;
	int				dead;
	int				all_eat;
	long long		time_start;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				left_fork;
	int				right_fork;
	t_data			*data;
	long long		last_meal_time;
	int				id;
	int				meals_eaten;
}	t_philo;

// main
void		*routine(void *arg);

// philos
int			death_status(t_data *data);
void		*death_monitor(void *arg);
int			is_dead(t_philo *philo);
int			death_check(t_philo *philo, long long death_time, long long n);
int			check_full(t_philo *philo);

// time
long long	time_to_print(long long time);
long long	get_time(void);
void		ft_usleep(long int time_ms);

// init
int			check_args(int ac, char **av);
void		one_philo(t_philo *philo);
void		init_mutexes(t_data *data);
void		init_data_struct(int ac, char **av, t_data *data);
void		init_philo(t_philo *philo, t_data *data);

// utils
int			right_fork(int left, int right);
int			left_fork(int right, int left);
int			ft_isdigit(char *s);
int			atoi_strict(char *num);
int			print_error(void);

// routine
void		write_status(t_philo *philo, char *s);
void		time_to_sleep(t_philo *philo);
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		cleanup_all(t_philo *philo);

#endif
