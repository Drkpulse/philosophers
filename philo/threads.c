/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 17:19:16 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_threads(t_rules *rules)
{
	int	num_philos;
	int	i;

	num_philos = get_num_philos(rules);
	i = 0;
	rules->time_start = get_time();
	while (i < num_philos)
	{
		if (pthread_create(&rules->philo_threads[i], NULL, \
			&routine, &rules->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&rules->grim_reaper, NULL, \
		&reaper_schythe, rules))
		return (1);
	if (num_meals_option(rules) == 1 && \
	pthread_create(&rules->monit_all_full, NULL, &all_full_routine, rules))
		return (1);
	return (0);
}

int	ft_threads_join(t_rules *rules)
{
	int	i;
	int	n_philos;

	n_philos = get_num_philos(rules);
	i = 0;
	if (pthread_join(rules->grim_reaper, NULL))
		return (1);
	if (num_meals_option(rules) == 1 && \
		pthread_join(rules->monit_all_full, NULL))
		return (1);
	while (i < n_philos)
	{
		if (pthread_join(rules->philo_threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
