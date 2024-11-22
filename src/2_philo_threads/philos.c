#include "philosophers.h"

void	fn_print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	fn_check_for_deaths(philo);
	timestamp = fn_get_timestamp(philo);
	printf("%lu philo nb %i %s\n", timestamp, philo->id, msg);
}

void	fn_sleep(t_philo *philo)
{
	fn_check_for_deaths(philo);
	fn_print_state(philo, "is sleeping");
	usleep(philo->shared_context->time_to_sleep * mSEC);
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
