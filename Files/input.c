#include "philo.h"

int	bad_input()
{
	printf("INPUT is Invalid\n");
	printf("./philo NB_Philo T_Die T_Eat T_Sleep (Num_Eat)\n");
	printf("1 <= NB_Philo <= 200\n");
	printf("T_* >= 60\n");
	printf("Num_Eat > 0\n");
	return (1);
}

int	is_valid_input (int argc, char **argv)
{
	int	i;

	i = 1;
	if(argc == 6 && ft_atoi(argv[5]) <= 0)
		return (1);
	if(ft_atoi(argv[i]) > 200 && ft_atoi(argv[i]) < 1)
		return (1);
	while (++i < 5)
	{
		if(ft_atoi(argv[i]) < 60)
			return (1);
	}
	return(0);
}

int	is_input_number(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	while(i < argc)
	{
		k = 0;
		while(argv[i][k] != '\0')
		{
			if(argv[i][k] > '9' || '0' > argv[i][k])
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		count;
	long	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 1;
	while (str[count] == '\r' || str[count] == '\t' || str[count] == ' '
		|| str[count] == '\f' || str[count] == '\v' || str[count] == '\n')
		count++;
	if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	if (!(str[count] >= '0' && str[count] <= '9'))
		return (0);
	while (str[count] >= '0' && str[count] <= '9')
		result = result * 10 + (str[count++] - '0');
	return (result * sign);
}

int	check_input(int argc, char **argv)
{
	if(argc > 6 || argc < 5)
		return (1);
	if(is_input_number(argc, argv))
		return (1);
	if(is_valid_input(argc, argv))
		return (1);
	return (0);
}