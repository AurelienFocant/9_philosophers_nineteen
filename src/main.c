#include "philosophers.h"

void	fn_join_threads(t_philo *philos)
{
	int	id;

	id = 0;
	while (id < philos->shared_context->nb_of_philo)
	{
		pthread_join(philos[id].thread, NULL);
		id++;
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_context		shared_context;
	t_philo			*philos;
	int				i;

	fn_check_args(argc, argv);
	forks = fn_init_forks(ft_atoi(argv[1]));
	shared_context = fn_setup_context(argv, forks);
	philos = fn_init_philos(&shared_context);
	i = 0;
	while (i < shared_context.nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, thread_routine, &philos[i]);
		i++;
	}
	fn_join_threads(philos);
	fn_cleanup_data(philos);
	return (EXIT_SUCCESS);
}
