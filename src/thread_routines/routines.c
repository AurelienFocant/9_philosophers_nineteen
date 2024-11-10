#include "philosophers.h"

t_context	fn_setup_context(char **argv, pthread_mutex_t *forks)
{
	t_context	context;

	pthread_mutex_init(&(context.death_mutex), NULL);
	context.is_dead[0] = FALSE;
	context.is_dead[1] = -1;
	context.nb_of_philo = ft_atoi(argv[1]);
	context.time_to_die = ft_atoi(argv[2]);
	context.time_to_eat = ft_atoi(argv[3]);
	context.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context.total_nb_of_meals = ft_atoi(argv[5]);
	context.forks = forks;
	return (context);
}

pthread_mutex_t	*fn_init_forks(t_context *context)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * context->nb_of_philo);
	if (!forks)
	{
		printf("malloc on forks failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < context->nb_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		// check return value of syscall !!!
		i++;
	}
	return (forks);
}

t_philo	*fn_init_philos(t_context *shared_context)
{ 
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * shared_context->nb_of_philo);
	if (!philos)
	{
		i = 0;
		while (i < shared_context->nb_of_philo)
			pthread_mutex_destroy(&(shared_context->forks[i++]));
		free(shared_context->forks);
		printf("malloc on philos failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		philos[i].id = i;
		philos[i].time_since_last_meal = fn_get_epoch_in_usec();
		philos[i].shared_context = shared_context;
		i++;
	}
	return (philos);
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
