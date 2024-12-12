#include "philo.h"

int	get_num_philos(t_rules *rules)
{
	int	i;

	pthread_mutex_init(&rules->n_philo);
	i = rules->n_philo;
	pthread_mutex_unlock(&rules->n_philo);
	return (i);
}

int	get_state(t_philo *philo)
{
	t_state state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}