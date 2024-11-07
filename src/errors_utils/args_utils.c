#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "philosophers.h"

bool	fn_check_args(int argc)
{
	if (argc < 5 || argc > 6)
		return (false);
	return (true);
}

void	fn_free_and_exit(pthread_mutex_t *forks, t_philo *philos, char *msg, t_context shared_context)
{
	int	i;
	(void) philos;

	i = 0;
	if (forks)
	{
		while (i < shared_context.nb_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			//free(forks[i]);
			i++;
		}
	}
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
