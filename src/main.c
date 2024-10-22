#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "libft.h"
#include "philosophers.h"

t_context	fn_setup_context(char **argv)
{
	t_context	context;

	context.nb_of_philo = ft_atoi(argv[1]);
	context.time_to_die = ft_atoi(argv[2]);
	context.time_to_eat = ft_atoi(argv[3]);
	context.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context.nb_of_meals = ft_atoi(argv[5]);
	return (context);
}

bool	fn_check_args(int argc)
{
	if (argc < 5 || argc > 6)
		return (false);
	return (true);
}

pthread_mutex_t	*fn_malloc_forks(t_context *context)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * context->nb_of_philo);
	i = 0;
	while (i < context->nb_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_context	context;
	
	if (!fn_check_args(argc))
	{
		printf("Invalid arguments\n");
		exit (EXIT_FAILURE);
	}
	context = fn_setup_context(argv);
	forks = fn_malloc_forks(&context);
	return (EXIT_SUCCESS);
}
