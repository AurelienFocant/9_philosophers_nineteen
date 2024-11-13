#include "philosophers.h"

t_context	fn_setup_context(char **argv, pthread_mutex_t *forks)
{
	t_context	context;

	context.time_of_start = fn_get_epoch_in_usec();
	pthread_mutex_init(&(context.death_mutex), NULL);
	context.is_dead[0] = FALSE;
	context.is_dead[1] = -1;
	context.nb_of_philo = ft_atoi(argv[1]);
	context.time_to_die = ft_atoi(argv[2]);
	context.time_to_eat = ft_atoi(argv[3]);
	context.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context.total_nb_of_meals = ft_atoi(argv[5]);
	return (context);
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
