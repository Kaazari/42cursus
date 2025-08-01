/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:26:36 by zdjitte           #+#    #+#             */
/*   Updated: 2025/07/18 20:26:37 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INT_MIN -2147483648
# define INT_MAX 2147483647

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				finished;
	long int		last_meal_time;
	pthread_t		thread_id;
	int				left_fork;
	int				right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				stop;
	int				finished_count;
	long int		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	time_eat_mutex;
	pthread_t		monitor_thread;
}	t_data;

// utils.c
long int	get_time(void);
void		ft_putnbr_fd(long int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_usleep(long int time_ms);
int			check_death(t_data *data, int set_death);
int			check_meals_completed(t_philo *philo);

// output.c
void		write_status(char *str, t_philo *philo);
void		log_state(t_data *data, int philo_id, char *message);
void		announce_death(t_data *data, int philo_id);
void		announce_finish(t_data *data);

// monitor.c
void		*death_monitor(void *arg);
int			check_all_philosophers_death(t_data *data);
void		*monitor_routine(void *arg);
int			check_philosopher_death(t_philo *philo);
int			all_philosophers_ate_enough(t_data *data);

// actions.c
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_down_forks(t_philo *philo);

// forks.c
void		sleep_philosopher(t_philo *philo);
void		think(t_philo *philo);
void		sleep_think(t_philo *philo);
void		handle_single_philosopher(t_philo *philo);

// routine.c
void		*philo_routine(void *arg);
void		*philosopher_routine_single(void *arg);
int			create_threads(t_data *data);
int			create_single_thread(t_data *data);
int			join_threads(t_data *data);

// init.c
void		init_simulation(t_data *data);
int			allocate_memory(t_data *data);
void		cleanup(t_data *data);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);

// cleanup.c
void		cleanup_simulation(t_data *data);
void		error_exit(t_data *data, char *message);
int			handle_error(t_data *data, int error_code, char *message);
void		destroy_mutexes(t_data *data);

// parsing.c
int			parse_args(int argc, char **argv, t_data *data);
int			atoi_strict(const char *str, int *result);

#endif
