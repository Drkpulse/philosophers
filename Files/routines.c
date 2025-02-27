#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		ft_yousleep(philo->rules->time_eat - 10);
	while (get_state(philo) != DEAD)
	{
		if (feed(philo) != 0)
			break;
		if (get_state(philo) == DEAD )
			break;
		if (ft_sleepy(philo) != 0)
			break;
		if (get_state(philo) == DEAD)
			break;
		if (ft_thinka(philo) != 0)
			break;
	}
	return (NULL);
}
