#include "philosophers.h"

void	fn_print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	fn_check_for_deaths(philo);
	timestamp = fn_get_timestamp(philo);
	(void) timestamp;
	fn_check_for_deaths(philo);
	pthread_mutex_lock(&(philo->shared_context->print_mutex));
	printf("%lu philo nb %i %s\n", fn_get_timestamp(philo), philo->id, msg);
	pthread_mutex_unlock(&(philo->shared_context->print_mutex));
}

void	fn_sleep(t_philo *philo)
{
	long	time_now;

	//printf("philo nb %i before checking death\n", philo->id);
	fn_check_for_deaths(philo);
	//printf("philo nb %i after checking death\n", philo->id);
	fn_print_state(philo, "is sleeping");
	while (true)
	{
		usleep(100);
		time_now = fn_get_epoch_in_usec();
		if (time_now >= (philo->time_of_last_meal + philo->shared_context->time_to_sleep))
			break ;
	}
}

void	*philos_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	while (true)
	{
		fn_try_to_eat(philo);
		fn_sleep(philo);
	}
}

bool	fn_philos_start_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->shared_context->nb_of_philo)
	{
		if (pthread_create
			(&(philos[i].thread), NULL, philos_routine, &philos[i])
			!= EXIT_SUCCESS)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
