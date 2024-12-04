#include "philosophers.h"

void	fn_print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->shared_context->print_mutex));
	printf("%lu philo nb %i %s\n", fn_get_timestamp(philo, PHILO), philo->id, msg);
	pthread_mutex_unlock(&(philo->shared_context->print_mutex));
}

void	fn_wrapper_usleep(long time_in_msec)
{
	long	time_now;

	time_now = fn_get_epoch_in_msec();
	while (fn_get_epoch_in_msec() - time_now < time_in_msec)
		usleep(100);
}

void	fn_sleep_and_think(t_philo *philo)
{
	fn_print_state(philo, "is sleeping");
	fn_wrapper_usleep(philo->shared_context->time_to_sleep);
	//usleep(philo->shared_context->time_to_sleep * 1000);
	fn_print_state(philo, "is thinking");
}

void	*philos_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	while (true)
	{
		fn_try_to_eat(philo);
		fn_sleep_and_think(philo);
	}
}

void	*one_philo_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	pthread_mutex_lock(&(OWN_FORK));
	fn_wrapper_usleep(philo->shared_context->time_to_die);
	fn_print_state(philo, "has taken a fork");
	pthread_exit(philo->thread);
}

bool	fn_philos_start_threads(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->shared_context->nb_of_philos == 1)
	{
		if (pthread_create
			(&(philos[i].thread), NULL, one_philo_routine, &philos[i])
			!= EXIT_SUCCESS)
			return (false);
		return (true);
	}
	while (i < philos->shared_context->nb_of_philos)
	{
		if (pthread_create
			(&(philos[i].thread), NULL, philos_routine, &philos[i])
			!= EXIT_SUCCESS)
			return (false);
		i++;
	}
	return (true);
}
