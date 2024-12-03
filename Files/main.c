#include "philo.h"

void	start_rules(t_rules *rules,char** argv)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat= ft_atoi(argv[3]);
	rules->time_sleep= ft_atoi(argv[4]);
	if(argv[5])
		rules->num_eat = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_rules rules;

	if (check_input(argc, argv))
		return(bad_input());
	//start_rules(&rules, argv);
}