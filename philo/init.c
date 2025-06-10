/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 19:52:47 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_forks(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = rules->philos;
	while (i < rules->n_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	i = 0;
	philos[0].left_f = &rules->forks[0];
	philos[0].right_f = &rules->forks[rules->n_philo - 1];
	i++;
	while (i < rules->n_philo)
	{
		philos[i].left_f = &rules->forks[i];
		philos[i].right_f = &rules->forks[i - 1];
		i++;
	}
	return (0);
}

int	start_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = rules->philos;
	while (i < rules->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		philos[i].state = IDLE;
		philos[i].meals_eaten = 0;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_meals_eaten, NULL);
		pthread_mutex_init(&philos[i].mut_last_meal_time, NULL);
		update_last_meal_time(&philos[i]);
		i++;
	}
	return (0);
}

int	malloc_rules(t_rules *rules)
{
	rules->philos = malloc(sizeof(t_philo) * rules->n_philo);
	if (rules->philos == NULL)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (rules->forks == NULL)
		return (free(rules->philos), (1));
	rules->philo_threads = malloc(sizeof(pthread_t) * rules->n_philo);
	if (rules->philo_threads == NULL)
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
	pthread_mutex_init(&rules->mut_print, NULL);
	pthread_mutex_init(&rules->mut_scythe, NULL);
}

int	start_rules(t_rules *rules, char **argv, int argc)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->num_philo_full = 0;
	rules->scythe = false;
	rules->time_start = get_time();
	rules->time_death = (uint64_t) ft_atoi(argv[2]);
	rules->time_eat = (uint64_t) ft_atoi(argv[3]);
	rules->time_sleep = (uint64_t) ft_atoi(argv[4]);
	rules->num_eat = -1;
	if (argc == 6)
		rules->num_eat = ft_atoi(argv[5]);
	mutex_init_rules(rules);
	return (malloc_rules(rules));
}
