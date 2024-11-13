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

void	fn_destroy_mutexes(t_philo *philos)
{
	t_philo *philo;
	int	id;

	philo = philos;
	id = 0;
	while (id < NB_PHILO)
	{
		pthread_mutex_destroy(&OWN_FORK);
		id++;
	}
}

void	fn_cleanup_data(t_philo *philos)
{
	fn_destroy_mutexes(philos);
	free(philos);
}

void	fn_free_and_exit(char *msg, t_philo *philos)
{
	if (philos)
		fn_cleanup_data(philos);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
