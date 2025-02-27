
#include "philo.h"

void	set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
}

void	set_scythe(t_rules *rules, bool set)
{
	pthread_mutex_lock(&rules->mut_scythe);
	rules->scythe = set;
	pthread_mutex_unlock(&rules->mut_scythe);
}
