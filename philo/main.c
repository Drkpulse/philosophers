/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/06/10 16:59:18 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(int argc, char **argv)
{
	t_rules rules;

	if(start_rules(&rules, argv, argc))
		return (1);
	start_philos(&rules);
	start_forks(&rules);
	exec_threads(&rules);
	ft_threads_join(&rules);
	janitor(&rules);
	return (0);
}

int main(int argc, char **argv)
{
	if (check_input(argc, argv))
		return(bad_input());
	if (philosophers(argc, argv))
		return (1);
	return (0);
}
