#include "philo.h"

void	drop_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
}

void	drop_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
}

int	take_left_fork(t_philo *philo)
{
	if(get_state(philo) == DEAD)
		return (0);
	pthread_mutex_lock(philo->left_f);
	write_msg(philo->rules, philo->id, "has taken a fork");
	return (1);
}

int	take_right_fork(t_philo *philo)
{
	if(get_state(philo) == DEAD)
		return (0);
	pthread_mutex_lock(philo->right_f);
	write_msg(philo->rules, philo->id, "has taken a fork");
	return (1);
}

int	take_the_forks(t_philo *philo)
{
	if (get_num_philos(philo->rules) == 1)
		return (solo_philo(philo));
	if (take_left_fork(philo))
		return (1);
	if (take_right_fork(philo))
		return (1);
	return (0);
}
