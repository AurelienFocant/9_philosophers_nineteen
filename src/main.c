#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "libft.h"
#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_context		shared_context;
	t_philo			*philos;
	int				i;

	if (!fn_check_args(argc))
	{
		printf("wrong args\n");
		return (EXIT_FAILURE);
	}
	forks = fn_init_forks(&shared_context);
	if (!forks)
		fn_free_and_exit(NULL, NULL, "malloc on forks failed", shared_context);
	shared_context = fn_setup_context(argv, forks);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		fn_free_and_exit(forks, NULL, "malloc on philos failed", shared_context);
	i = 0;
	while (i < shared_context.nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, thread_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < shared_context.nb_of_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
