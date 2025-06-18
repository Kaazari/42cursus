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
// 	int					finished;
// 	long long			last_meal;
// 	pthread_t			death_thread_id;
// }				t_philo;

// void	*t_routine();
// void	create_threads(int nb, t_data *data);
// void	struct_define(char **av);

// #endif

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int eating;
	pthread_t		thread_id;
	pthread_t		death_thread;
	pthread_t monitor_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	meal_mutex;
	long long		last_meal_time;
	int	meals_eaten;
	int				finished;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int eating_count;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t eating_mutex;
	int				finished_count;
	int				someone_died;
	pthread_t   monitor_thread;  // <- Ajouter cette ligne
	pthread_t		*threads;
	t_philo			*philos;
}	t_data;

// Time functions
long long	get_time(void);
void		precise_usleep(long long time_ms);

// Status and monitoring functions
int			check_death(t_data *data, int set_death);
void		write_status(char *str, t_philo *philo);
void		*death_monitor(void *arg);

// Utility functions
int			ft_atoi_safe(const char *str);
void		ft_putnbr_fd(long long n, int fd);
void		ft_putstr_fd(char *s, int fd);

// Philosopher routines
void		*philo_routine(void *arg);
void		eat_activity(t_philo *philo);
void		sleep_think(t_philo *philo);

// Initialization and cleanup
int			init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);
int			init_philosophers(t_data *data);
int			create_threads(t_data *data);
int			wait_for_completion(t_data *data);
int			parse_arguments(int argc, char **argv, t_data *data);
int			allocate_memory(t_data *data);
void		cleanup(t_data *data);

#endif
