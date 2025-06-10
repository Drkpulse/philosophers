/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mood_swings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 16:59:23 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	drop_right_fork(philo);
	drop_left_fork(philo);
	return (0);
}
