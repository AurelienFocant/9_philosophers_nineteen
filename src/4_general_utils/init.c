#include "philosophers.h"

bool	fn_check_args(int argc, char **argv)
{
	(void) argv;
	if (argc < 5 || argc > 6)
	{
		printf("wrong args\n");
		exit(EXIT_FAILURE);
	}
	return (true);
}

bool	fn_setup_context(t_context *context, char **argv)
{
	if (pthread_mutex_init(&(context->death_mutex), NULL) != EXIT_SUCCESS)
		return (false);
	if (pthread_mutex_init(&(context->print_mutex), NULL) != EXIT_SUCCESS)
		return (false);
	context->time_of_start = fn_get_epoch_in_usec();
	context->is_dead = false;
	context->nb_of_philo = ft_atoi(argv[1]);
	context->time_to_die = ft_atoi(argv[2]);
	context->time_to_eat = ft_atoi(argv[3]);
	context->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context->total_nb_of_meals = ft_atoi(argv[5]);
	else
		context->total_nb_of_meals = -1;
	return (true);
}

t_philo	*fn_init_philos(t_context *shared_context)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * shared_context->nb_of_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		if (pthread_mutex_init(&(philos[i].fork), NULL) != EXIT_SUCCESS)
		{
			free(philos);
			return (NULL);
		}
		philos[i].id = i;
		philos[i].time_of_last_meal = fn_get_epoch_in_usec();
		philos[i].meals_eaten = 0;
		philos[i].shared_context = shared_context;
		i++;
	}
	shared_context->philos = philos;
	return (philos);
}
