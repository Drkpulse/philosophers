#include "philo.h"


int	philosophers(int argc, char **argv)
{
	t_rules rules;

	if(start_rules(&rules, argv, argc))
		return (1);
	//printf("Rules started\n");
	start_philos(&rules);
	//printf("Philos started\n");
	start_forks(&rules);
	//printf("Forks started\n");
	exec_threads(&rules);
	//printf("Threads started\n");
	ft_threads_join(&rules);
	//printf("Threads joined\n");
	janitor(&rules);
	//printf("Janitor done\n");
	return (0);
}

int main(int argc, char **argv)
{
	if (check_input(argc, argv))
		return(bad_input());
	//printf("INPUT is valid\n");
	if (philosophers(argc, argv))
		return (1);
	return (0);
}
