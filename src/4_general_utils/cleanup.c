#include "philosophers.h"

void	fn_destroy_mutexes(t_philo *philo)
{
	int	id;

	id = 0;
	while (id < NB_PHILO)
	{
		pthread_mutex_destroy(&(philo[id].fork));
		id++;
	}
	pthread_mutex_destroy(&philo->shared_context->death_mutex);
	pthread_mutex_destroy(&philo->shared_context->print_mutex);
	pthread_mutex_destroy(&philo->shared_context->satiation_mutex);
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

void	fn_join_threads(t_banshee *banshee, t_philo *philos)
{
	int	id;

	if (banshee)
		pthread_join(banshee->thread, NULL);
	if (philos)
	{
		id = 0;
		while (id < philos->shared_context->nb_of_philos)
		{
			pthread_join(philos[id].thread, NULL);
			id++;
		}
	}
}
