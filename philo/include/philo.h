/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:48:53 by evdos-sa          #+#    #+#             */
/*   Updated: 2023/09/18 19:28:38 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* -------------------------------------------------------------------------- */
/*  								LIBRARIES								  */
/* -------------------------------------------------------------------------- */
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

/* -------------------------------------------------------------------------- */
/*  								MACROS									  */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/*  				Macros to print the philosopher's action				  */
/* -------------------------------------------------------------------------- */
# define TAKE_FORKS "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/* -------------------------------------------------------------------------- */
/*  								STRUCTURES								  */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/*  				Structure for the state of the philosopher				  */
/* -------------------------------------------------------------------------- */
typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

/* -------------------------------------------------------------------------- */
/*  				Structure for the philosophers and forks				  */
/* -------------------------------------------------------------------------- */
typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_nb_meals_had;
	pthread_mutex_t	mut_last_eat_time;
	u_int64_t		last_eat_time;
}t_philo;

/* -------------------------------------------------------------------------- */
/*  					General structure of the program					  */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	int				nb_philos;
	int				nb_meals;
	int				nb_full_p;
	bool			keep_iterating;
	u_int64_t		eat_time;
	u_int64_t		die_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	mut_eat_t;
	pthread_mutex_t	mut_die_t;
	pthread_mutex_t	mut_sleep_t;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}t_data;

/* -------------------------------------------------------------------------- */
/*  						DECLARATION OF FUNCTIONS						  */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/*  							phil_action_eat.c							  */
/* -------------------------------------------------------------------------- */

bool		is_philo_full(t_data *data, t_philo *philo);
void		update_last_meal_time(t_philo *philo);
void		update_nb_meals_had(t_philo *philo);
void		sleep_for_eating(t_philo *philo);
int			eat(t_philo *philo);

/* -------------------------------------------------------------------------- */
/*  							phil_actions.c								  */
/* -------------------------------------------------------------------------- */

int			ft_sleep(t_philo *philo);
void		ft_usleep(uint64_t sleep_time);
int			think(t_philo *philo);
bool		philo_died(t_philo *philo);
void		wait_until(u_int64_t wakeup_time);

/* -------------------------------------------------------------------------- */
/*  							phil_cheack_routine.c						  */
/* -------------------------------------------------------------------------- */

void		notify_all_philos(t_data *data);
void		*all_full_routine(void *data_p);
void		*all_alive_routine(void *data_p);
void		*routine(void *philo_p);

/* -------------------------------------------------------------------------- */
/*  							phil_forks_take_drop.c						  */
/* -------------------------------------------------------------------------- */

void		drop_left_fork(t_philo *philo);
void		drop_right_fork(t_philo *philo);
int			take_left_fork(t_philo *philo);
int			take_right_fork(t_philo *philo);
int			take_forks(t_philo *philo);

/* -------------------------------------------------------------------------- */
/*  							phil_get_times.c							  */
/* -------------------------------------------------------------------------- */

uint64_t	get_start_time(t_data *data);
uint64_t	get_die_time(t_data *data);
uint64_t	get_sleep_time(t_data *data);
uint64_t	get_eat_time(t_data *data);
uint64_t	get_last_eat_time(t_philo *philo);

/* -------------------------------------------------------------------------- */
/*  							phil_get_utils.c							  */
/* -------------------------------------------------------------------------- */

bool		get_keep_iter(t_data *data);
int			get_nb_philos(t_data *data);
t_state		get_philo_state(t_philo *philo);
int			get_nb_meals_philo_had(t_philo *philo);
u_int64_t	get_time(void);

/* -------------------------------------------------------------------------- */
/*  							phil_init.c									  */
/* -------------------------------------------------------------------------- */

int			init_forks(t_data *data);
int			init_philos(t_data *data);
int			malloc_data_pointers(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
int			philosophers(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*  							phil_main.c									  */
/* -------------------------------------------------------------------------- */

int			ph_error(void);
int			ft_atoi(char *str);
int			ph_is_digit(int ac, char **av);
int			main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*  							phil_threads.c								  */
/* -------------------------------------------------------------------------- */

int			run_threads(t_data *data);
int			join_threads(t_data *data);
int			just_one_philo(t_philo *philo);
void		set_keep_iterating(t_data *data, bool set_to);
void		set_philo_state(t_philo *philo, t_state state);

/* -------------------------------------------------------------------------- */
/*  							phil_utils.c								  */
/* -------------------------------------------------------------------------- */

bool		nb_meals_option(t_data *data);
void		print_nb_meals_had(t_philo *philo);
void		print_msg(t_data *data, int id, char *msg);
void		print_mut(t_data *data, char *msg);
void		free_data(t_data *data);

#endif