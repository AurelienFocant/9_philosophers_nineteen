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
	t_context		shared_context;
	t_philo			*philos;
	int				i;

	if (!fn_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!fn_setup_context(&shared_context, argv))
		return (EXIT_FAILURE);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, thread_routine, &philos[i]);
		i++;
	}
	fn_join_threads(philos);
	fn_cleanup_data(philos);
	return (EXIT_SUCCESS);
}
