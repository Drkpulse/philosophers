
#include "philo.h"

int	ft_thinka(t_philo *philo)
{
	set_philo_state(philo, THINKING);
	if (get_state(philo) == DEAD)
		return (1);
	write_msg(philo->rules, philo->id, "is thinking");
	return (0);
}

int	ft_sleepy(t_philo *philo)
{
	set_philo_state(philo, SLEEPING);
	if (get_state(philo) == DEAD)
		return (1);
	write_msg(philo->rules, philo->id, "is sleeping");
	ft_yousleep(get_time_sleep(philo->rules));
	return (0);
}

int	feed(t_philo *philo)
{
	if(take_the_forks(philo) != 0)
		return (1);
	set_philo_state(philo, EATING);
	update_last_meal_time(philo);
	write_msg(philo->rules, philo->id, "is eating");
	ft_yousleep(get_time_eat(philo->rules));
	update_meals_eaten(philo);
	//printf("Philosopher %d last ate at %lu\n", philo->id, get_last_meal_time(philo) - get_time_start(philo->rules));
	//printf("Philosopher %d has eaten %d meals\n", philo->id, get_meals_eaten(philo));
	drop_right_fork(philo);
	drop_left_fork(philo);
	return (0);
}
