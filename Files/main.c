#include "philo.h"

start_rules(t_rules rules,char** argv)
{

}

int main(int argc, char **argv)
{
	t_rules rules;

	if (argc != 5 && argc != 6)
		return(1);
	start_rules(&rules, argv);
}