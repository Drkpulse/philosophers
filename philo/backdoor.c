/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backdoor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/18 22:44:10 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_full(t_rules *rules, t_philo *philo)
{
	bool	isfull;

	isfull = false;
	if (get_meals_eaten(philo) >= rules->num_eat)
	{
		isfull = true;
		set_philo_state(philo, FULL);
	}
	return (isfull);
}

bool	is_philo_dead(t_philo *philo)
{
	bool	isdead;
	t_rules	*rules;

	rules = philo->rules;
	isdead = false;
	if (get_time() - get_last_meal_time(philo) > get_time_death(rules)
		&& get_state(philo) != EATING)
	{
		isdead = true;
		set_philo_state(philo, DEAD);
	}
	return (isdead);
}

void	msg_philos(t_rules *rules)
{
	t_philo	*philos;
	int		n_philos;
	int		i;

	philos = rules->philos;
	n_philos = get_num_philos(rules);
	i = 0;
	while (i < n_philos)
	{
		set_philo_state(&philos[i], DEAD);
		i++;
	}
}

void	*all_full_routine(void *rules_pointer)
{
	t_rules	*rules;
	int		n_philos;
	bool	all_full;

	rules = (t_rules *)rules_pointer;
	n_philos = get_num_philos(rules);
	while (!get_scythe(rules))
	{
		all_full = are_they_full(rules, n_philos);
		if (all_full && !get_scythe(rules))
		{
			set_scythe(rules, true);
			msg_philos(rules);
			break ;
		}
		ft_yousleep(100);
	}
	return (NULL);
}

void	*reaper_schythe(void *rules_pointer)
{
	t_rules	*rules;
	t_philo	*philos;
	int		n_philos;
	int		i;

	rules = (t_rules *)rules_pointer;
	philos = rules->philos;
	n_philos = get_num_philos(rules);
	i = 0;
	while (i < rules->n_philo && !get_scythe(rules))
	{
		if (is_philo_dead(&philos[i]) && !get_scythe(rules))
		{
			write_msg(rules, philos[i].id, "died");
			set_scythe(rules, true);
			msg_philos(rules);
			break ;
		}
		i = (i + 1) % n_philos;
		usleep(1000);
	}
	return (NULL);
}
