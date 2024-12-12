#include "philo.h"

int	feed(t_philo *philo)
{
	if(take_the_forks(philo))
		return (1);
}

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		getsleep(philo->rules->time_eat - 10);
	while(get_state(philo) != DEAD)
	{
		if (feed(philo))
			break;
		if (get_state(philo) != DEAD)
			break;
		if (sleepy(philo))
			break;
		if (get_state(philo) != DEAD)
			break;
		if (thinka(philo))
			break;
	}
	return (NULL);
}