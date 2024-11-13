#include "philosophers.h"

void	fn_lock_neighbour_fork(t_philo *philo)
{
	long	timestamp;

	if (philo->id % 2)
		pthread_mutex_lock(&(LEFT_FORK));
	else
		pthread_mutex_lock(&(RIGHT_FORK));
	timestamp = fn_get_timestamp(philo);
	printf("%lu philo nb %i picked other fork\n", timestamp, philo->id);
}

void	fn_lock_own_fork(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&(OWN_FORK));
	timestamp = fn_get_timestamp(philo);
	printf("%lu philo nb %i picked own fork\n", timestamp, philo->id);
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
	long	time_of_meal;
	long	time_now;
	long	timestamp;
	int		time_to_eat;

	time_to_eat = philo->shared_context->time_to_eat * mSEC;
	time_of_meal = fn_get_epoch_in_usec();
	timestamp = fn_get_timestamp(philo);
	printf("%lu philo nb %i is eatin\n", timestamp, philo->id);
	while (TRUE)
	{
		time_now = fn_get_epoch_in_usec();
		if (time_now >= (time_of_meal + time_to_eat))
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
	fn_check_for_deaths(philo);
}
