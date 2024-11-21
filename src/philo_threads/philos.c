#include "philosophers.h"

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

void	fn_philos_start_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->shared_context->nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, philos_routine, &philos[i]);
		// check return value of syscall
		i++;
	}
}
