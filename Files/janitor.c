#include "philo.h"

void	cleaning_lady(t_rules *rules)
{
	free(rules->philo_threads);
	free(rules->philos);
	free(rules->forks);
	pthread_mutex_destroy(&rules->mut_time_eat, NULL);
	pthread_mutex_destroy(&rules->mut_time_death, NULL);
	pthread_mutex_destroy(&rules->mut_time_sleep, NULL);
	pthread_mutex_destroy(&rules->mut_n_philos, NULL);
	pthread_mutex_destroy(&rules->mut_time_start, NULL);
}