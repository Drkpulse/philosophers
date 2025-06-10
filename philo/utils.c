/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 19:50:43 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	num_meals_option(t_rules *rules)
{
	if (rules->num_eat > 0)
		return (true);
	return (false);
}

int	solo_philo(t_philo *philo)
{
	take_left_fork(philo);
	ft_yousleep(get_time_death(philo->rules));
	set_philo_state(philo, DEAD);
	return (1);
}

void	janitor(t_rules *rules)
{
	int	i;
	int	n_philos;

	n_philos = get_num_philos(rules);
	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].mut_state);
		pthread_mutex_destroy(&rules->philos[i].mut_meals_eaten);
		pthread_mutex_destroy(&rules->philos[i].mut_last_meal_time);
		i++;
	}
	pthread_mutex_destroy(&rules->mut_time_death);
	pthread_mutex_destroy(&rules->mut_time_eat);
	pthread_mutex_destroy(&rules->mut_time_sleep);
	pthread_mutex_destroy(&rules->mut_n_philos);
	pthread_mutex_destroy(&rules->mut_print);
	pthread_mutex_destroy(&rules->mut_time_start);
	pthread_mutex_destroy(&rules->mut_scythe);
	free(rules->forks);
	free(rules->philos);
	free(rules->philo_threads);
}

void	write_msg(t_rules *rules, int id, char *msg)
{
	uint64_t	time;

	time = get_time() - get_time_start(rules);
	pthread_mutex_lock(&rules->mut_print);
	if (!get_scythe(rules))
		printf("%lu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&rules->mut_print);
}

void	ft_yousleep(uint64_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}
