#include "philo.h"

int	drop_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
}

int	drop_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
}

int	take_left_fork(t_philo *philo)
{
	if(get_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->left_f);
	//print
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if(get_state(philo) == DEAD)
		return (0);
	pthread_mutex_lock(philo->right_f);
	//print
	return (0);
}

int	take_the_forks(t_philo *philo)
{
	//Make one philo
	if (take_right_fork(philo))
		return (1);
	if(take_left_fork(philo))
	{
		drop_right_fork(philo);
		return (1);
	}
	return (0);
}