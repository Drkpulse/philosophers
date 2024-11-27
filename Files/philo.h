
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct rules
{
	int	n_philo;
	int	time_death;
	int	time_eat;
	int	time_sleep;
	int	num_eat;
	int	gone;

}	t_rules;

typedef struct s_philo {
    int id;
    long last_meal_time;
    int meals_eaten;
    t_rules *rules;
    pthread_t thread;
} t_philo;
