/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 17:06:18 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_num_philos(t_rules *rules)
{
	int	n_philos;

	pthread_mutex_lock(&rules->mut_n_philos);
	n_philos = rules->n_philo;
	pthread_mutex_unlock(&rules->mut_n_philos);
	return (n_philos);
}

int	get_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

bool	get_scythe(t_rules *rules)
{
	bool	scythe;

	pthread_mutex_lock(&rules->mut_scythe);
	scythe = rules->scythe;
	pthread_mutex_unlock(&rules->mut_scythe);
	return (scythe);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(&philo->mut_meals_eaten);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->mut_meals_eaten);
	return (meals_eaten);
}

uint64_t	get_last_meal_time(t_philo *philo)
{
	uint64_t	last_meal_time;

	pthread_mutex_lock(&philo->mut_last_meal_time);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mut_last_meal_time);
	return (last_meal_time);
}
