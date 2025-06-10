/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 17:15:18 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

struct	s_rules;

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

typedef struct s_philo
{
	int				id;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_meals_eaten;
	pthread_mutex_t	mut_last_meal_time;
	bool			is_alive;
	int				meals_eaten;
	uint64_t		last_meal_time;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				n_philo;
	uint64_t		time_death;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		time_start;
	int				num_philo_full;
	int				num_eat;
	bool			scythe;
	pthread_mutex_t	mut_time_eat;
	pthread_mutex_t	mut_time_death;
	pthread_mutex_t	mut_time_sleep;
	pthread_mutex_t	mut_n_philos;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_time_start;
	pthread_mutex_t	mut_scythe;
	pthread_t		grim_reaper;
	pthread_t		monit_all_full;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_rules;

// INPUT VALIDATIONS FUNCTIONS
int			check_input(int argc, char **argv);
int			bad_input(void);

// CONVERTERS
int			ft_atoi(char *str);

// START RULES
int			start_rules(t_rules *rules, char **argv, int argc);

// START PHILO
int			start_philos(t_rules *rules);
int			start_forks(t_rules *rules);

// THREADS
int			exec_threads(t_rules *rules);
int			ft_threads_join(t_rules *rules);
void		*routine(void *philo_pointer);
void		*reaper_schythe(void *rules_pointer);
void		*all_full_routine(void *rules_pointer);

// SOLO
int			solo_philo(t_philo *philo);
int			take_left_fork(t_philo *philo);

// STATES
int			feed(t_philo *philo);
int			ft_thinka(t_philo *philo);
int			ft_sleepy(t_philo *philo);

// GET
int			get_state(t_philo *philo);
int			get_num_philos(t_rules *rules);
bool		get_scythe(t_rules *rules);
int			get_meals_eaten(t_philo *philo);
uint64_t	get_last_meal_time(t_philo *philo);
uint64_t	get_time_start(t_rules *rules);
uint64_t	get_time_sleep(t_rules *rules);

// SET
void		set_philo_state(t_philo *philo, t_state state);
void		set_scythe(t_rules *rules, bool set);

// TIME
uint64_t	get_time(void);
void		ft_yousleep(uint64_t sleep_time);
uint64_t	get_time_death(t_rules *rules);
uint64_t	get_time_eat(t_rules *rules);

// OPTION
bool		num_meals_option(t_rules *rules);

// UPDATES
void		update_last_meal_time(t_philo *philo);
void		update_meals_eaten(t_philo *philo);

//FORKS
int			take_the_forks(t_philo *philo);
void		drop_left_fork(t_philo *philo);
void		drop_right_fork(t_philo *philo);

// WRITE
void		write_msg(t_rules *rules, int id, char *msg);

// CLEAN
void		janitor(t_rules *rules);
#endif
