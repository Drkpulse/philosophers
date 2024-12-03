#include "philo.h"


int	philosophers(int argc, char **argv)
{
	t_rules rules;

	if(start_rules(&rules, argv, argc))
		return (1);
	//init_philo();
	//Forks;
	//Threads
	//join_threads
	//free everything
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