#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		ft_yousleep(philo->rules->time_eat);
	while (get_state(philo) != DEAD && !get_scythe(philo->rules))
	{
		if (feed(philo))
			break;
		if (get_state(philo) == DEAD && get_scythe(philo->rules))
			break;
		if (ft_sleepy(philo))
			break;
		if (get_state(philo) == DEAD && get_scythe(philo->rules))
			break;
		if (ft_thinka(philo))
			break;
	}
	return (NULL);
}
