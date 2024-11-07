#include "philosophers.h"

t_context	fn_setup_context(char **argv, pthread_mutex_t *forks)
{
	t_context	context;

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
		return (NULL);
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
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * shared_context->nb_of_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		philo[i].id = i;
		philo[i].shared_context = shared_context;
		i++;
	}
	return (philo);
}

void	*thread_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	while (true)
	{
		// eat
		fn_eat(philo);	
		// sleep
		fn_sleep(philo);
		// think
		fn_think(philo);
	}
}
