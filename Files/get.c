#include "philo.h"

int	get_num_philos(t_rules *rules)
{
	int	i;

	pthread_mutex_init(&rules->n_philo);
	i = rules->n_philo;
	pthread_mutex_unlock(&rules->n_philo);
	return (i);
}