

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

typedef struct s_rules
{
	int				n_philo;
	u_int64_t		time_death;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
	u_int64_t		time_start;
	int				num_philo_full;
	int				num_eat;
	pthread_mutex_t	mut_time_eat;
	pthread_mutex_t	mut_time_death;
	pthread_mutex_t	mut_time_sleep;
	pthread_mutex_t	mut_n_philos;
	pthread_mutex_t	mut_time_start;
	pthread_t		grim_reaper;
	pthread_t		monit_all_full;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_rules;

typedef struct s_philo {
	int				id;
	t_state			state;
	t_rules			*rules;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_meals_eaten;
	pthread_mutex_t	mut_last_meal_time;
	bool			is_alive;
	int				meals_eaten;
	u_int64_t		last_meal_time;
}				t_philo;

// INPUT VALIDATIONS FUNCTIONS
int	check_input(int argc, char **argv);
int	bad_input();

// CONVERTERS
int	ft_atoi(char *str);

// START RULES
int	start_rules(t_rules *rules,char** argv, int argc);

// START PHILO
int	start_philos(t_rules *rules);
int	start_forks(t_rules *rules);

// THREADS
int	exec_threads(t_rules *rules);

// GET
int	get_state(t_philo *philo);
int	get_num_philos(t_rules *rules);

// TIME
u_int64_t	get_time(void);

// OPTION
bool	num_meals_option(t_rules *rules);

// UPDATES
void	update_last_meal_time(t_philo *philo);

//FORKS
int	take_the_forks(t_philo *philo);
#endif