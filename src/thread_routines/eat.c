#include "philosophers.h"

void	fn_lock_neighbour_fork(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&(LEFT_FORK));
	else
		pthread_mutex_lock(&(RIGHT_FORK));
	printf("philo nb %i picked neighbour's fork\n", philo->id);
}

void	fn_lock_own_fork(t_philo *philo)
{
	pthread_mutex_lock(&(OWN_FORK));
	printf("philo nb %i picked own fork\n", philo->id);
}

void	fn_unlock_neighbour_fork(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_unlock(&(LEFT_FORK));
	else
		pthread_mutex_unlock(&(RIGHT_FORK));
}

void	fn_unlock_own_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(OWN_FORK));
}

void	fn_eat(t_philo *philo)
{
	long	time_start;
	long	time_now;
	int		time_to_eat;

	time_to_eat = philo->shared_context->time_to_eat * mSEC;
	time_start = fn_get_epoch_in_usec();
	printf("philo nb %i is eatin\n", philo->id);
	while (TRUE)
	{
		time_now = fn_get_epoch_in_usec();
		if (time_now >= (time_start + time_to_eat))
			break;
	}
}

void	fn_try_to_eat(t_philo *philo)
{
	fn_check_for_deaths(philo);
	fn_lock_neighbour_fork(philo);
	fn_check_for_deaths(philo);
	fn_lock_own_fork(philo);
	fn_check_for_deaths(philo);
	fn_update_time_last_meal(philo);
	fn_eat(philo);
	fn_unlock_neighbour_fork(philo);
	fn_check_for_deaths(philo);
	fn_unlock_own_fork(philo);
}
