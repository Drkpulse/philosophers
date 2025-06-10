/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 16:59:38 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		ft_yousleep(philo->rules->time_eat - 10);
	while (get_state(philo) != DEAD)
	{
		if (feed(philo) != 0)
			break;
		if (get_state(philo) == DEAD )
			break;
		if (ft_sleepy(philo) != 0)
			break;
		if (get_state(philo) == DEAD)
			break;
		if (ft_thinka(philo) != 0)
			break;
	}
	return (NULL);
}
