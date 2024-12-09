#include "philo.h"

bool	num_meals_option(t_rules *rules)
{
	if(rules->num_eat > 0)
		return (true);
	return (false);
}