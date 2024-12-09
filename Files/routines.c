#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	//last_meal_time
	if (philo->id % 2 == 0)
		getsleep(philo->rules->time_eat - 10);
	while(get_state(philo) != DEAD)
	{
		//EAT
		//CHECK DEAD
		//SLEEP
		//CHECK DEAD
		//THINK
	}
}