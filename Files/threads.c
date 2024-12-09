#include "philo.h"

int	exec_threads(t_rules *rules)
{
	int	num_philos;
	int	i;

	num_philos = get_num_philos(&rules);
	i = 0;
	rules->time_start = gettime();
	while (i++ < num_philos - 1)
		if(pthread_create(&rules->philo_threads[i], NULL, &routine, &rules->philos[i]))
			return (1);
	if (pthread_create(&rules->grim_reaper, NULL, &reaper_schythe, rules))
		return (1);
	if (num_meals_option(rules) == TRUE && pthread_create(&rules->monit_all_full, NULL, &all_full_routine, rules))
		return (1);
	return (0);
}