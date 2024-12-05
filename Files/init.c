#include "philo.h"

int	malloc_rules(t_rules *rules)
{
	rules->philos = malloc(sizeof(t_philo) * rules->n_philo);
	if(rules->philos == NULL)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if(rules->forks == NULL)
		return (free(rules->philos),(1));
	rules->philo_threads = malloc(sizeof(pthread_t) * rules->n_philo)
	if(rules->philo_threads == NULL)
		return (free(rules->philos), free(rules->forks), (1));
	return (0);
}
void	mutex_init_rules(t_rules *rules)
{
	pthread_mutex_init(&rules->mut_time_eat, NULL);
	pthread_mutex_init(&rules->mut_time_death, NULL);
	pthread_mutex_init(&rules->mut_time_sleep, NULL);
	pthread_mutex_init(&rules->mut_n_philos, NULL);
	pthread_mutex_init(&rules->mut_time_start, NULL);
}

int	start_rules(t_rules *rules,char** argv, int argc)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->num_philo_full = 0;
	rules->time_death = (u_int64_t) ft_atoi(argv[2]);
	rules->time_eat= (u_int64_t) ft_atoi(argv[3]);
	rules->time_sleep= (u_int64_t) ft_atoi(argv[4]);
	rules->num_eat = -1;
	if(argc == 6)
		rules->num_eat = ft_atoi(argv[5]);
	mutex_init_rules(rules);
	return (malloc_rules(rules));
}