#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	get_time_sleep(t_rules *rules)
{
	uint64_t	time_sleep;

	pthread_mutex_lock(&rules->mut_time_sleep);
	time_sleep = rules->time_sleep;
	pthread_mutex_unlock(&rules->mut_time_sleep);
	return (time_sleep);
}

uint64_t	get_time_death(t_rules *rules)
{
	uint64_t	time_death;

	pthread_mutex_lock(&rules->mut_time_death);
	time_death = rules->time_death;
	pthread_mutex_unlock(&rules->mut_time_death);
	return (time_death);
}

uint64_t	get_time_eat(t_rules *rules)
{
	uint64_t	time_eat;

	pthread_mutex_lock(&rules->mut_time_eat);
	time_eat = rules->time_eat;
	pthread_mutex_unlock(&rules->mut_time_eat);
	return (time_eat);
}

uint64_t	get_time_start(t_rules *rules)
{
	uint64_t	time_start;

	pthread_mutex_lock(&rules->mut_time_start);
	time_start = rules->time_start;
	pthread_mutex_unlock(&rules->mut_time_start);
	return (time_start);
}
