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
	long long		last_meal_time;
	pthread_t		death_thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	int				finished_count;
	long long		start_time;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	finish_mutex;
}	t_data;

// utils.c
long long	get_time(void);
void		ft_putnbr_fd(long long n, int fd);
void		ft_putstr_fd(char *s, int fd);
int			parse_number(char *str, int *i);
int			ft_atoi_safe(char *str);
void		precise_usleep(long long time_ms);
int			check_death(t_data *data, int set_death);

// output.c
void		print_status_message(t_philo *philo, char *str);
void		write_status(char *str, t_philo *philo);
void		print_death_message(t_philo *philo);

// monitor.c
int			check_philosopher_death(t_philo *philo);
void		*death_monitor(void *arg);

// actions.c
void		sleep_think(t_philo *philo);
void		get_fork_order(t_philo *philo, pthread_mutex_t **first,
				pthread_mutex_t **second);
void		handle_single_philosopher(t_philo *philo);
void		eating_process(t_philo *philo);
void		eat_activity(t_philo *philo);

// routine.c
void		handle_initial_delay(t_philo *philo);
int			check_meals_completed(t_philo *philo);
int			handle_philosopher_finished(t_philo *philo);
void		*philo_routine(void *arg);

// init.c
int			init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);
void		init_philosopher_data(t_data *data, int i);
void		assign_right_fork(t_data *data, int i);
int			init_philosophers(t_data *data);

// threads.c
int			create_threads(t_data *data);
int			wait_for_completion(t_data *data);

// parsing.c
int			validate_arguments(t_data *data);
int			parse_optional_argument(int argc, char **argv, t_data *data);
int			parse_arguments(int argc, char **argv, t_data *data);
int			allocate_memory(t_data *data);
void		cleanup(t_data *data);

#endif
