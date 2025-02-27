#include "philo.h"

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mut_last_meal_time);
}

void	update_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mut_meals_eaten);
}
