#include "philosophers.h"

bool	fn_setup_context(t_context *context, char **argv)
{
	if (pthread_mutex_init(&(context->death_mutex), NULL) != EXIT_SUCCESS)
	{
		printf("error death mutex init\n");
		return (false);
	}
	context->time_of_start = fn_get_epoch_in_usec();
	context->is_dead[0] = FALSE;
	context->is_dead[1] = -1;
	context->nb_of_philo = ft_atoi(argv[1]);
	context->time_to_die = ft_atoi(argv[2]);
	context->time_to_eat = ft_atoi(argv[3]);
	context->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context->total_nb_of_meals = ft_atoi(argv[5]);
	return (true);
}

void	*thread_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	while (true)
	{
		// eat
		fn_try_to_eat(philo);	
		// sleep
		fn_sleep(philo);
	}
}

t_philo	*fn_init_philos(t_context *shared_context)
{ 
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * shared_context->nb_of_philo);
	if (!philos)
	{
		printf("error mallocing philos\n");
		return (NULL);
	}
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		if (pthread_mutex_init(&(philo[i].fork)) != EXIT_SUCCESS)
		{
			printf("error initiating forks\n");
			free (philos);
			return (NULL);
		}
		philos[i].id = i;
		philos[i].time_since_last_meal = fn_get_epoch_in_usec();
		philo[i].meals_eaten = 0;
		philos[i].shared_context = shared_context;
		i++;
	}
	return (philos);
}
