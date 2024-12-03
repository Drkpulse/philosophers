

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>

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
	int	n_philo;
	u_int64_t	time_death;
	u_int64_t	time_eat;
	u_int64_t	time_sleep;
	u_int64_t	time_start;
	int	num_eat;

}	t_rules;

typedef struct s_philo {
	int	id;
	t_state	state;
	t_rules	*rules;
	pthread_t	thread;
	int	meals_eaten;
	u_int64_t	last_meal_time;
}	t_philo;

// INPUT VALIDATIONS FUNCTIONS
int	check_input(int argc, char **argv);
int	bad_input();

// CONVERTERS
int	ft_atoi(char *str);
#endif