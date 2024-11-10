#include "philosophers.h"

void	fn_update_time_last_meal(t_philo *philo)
{
	philo->time_since_last_meal = fn_get_epoch_in_usec();
}

bool	fn_is_starving(t_philo *philo)
{
	long	time_now;

	(void) time_now;
	(void) philo;
	return (true);
}

long	fn_get_epoch_in_usec(void)
{
	struct timeval	timeval;
	long			epoch;

	gettimeofday(&timeval, NULL);
	// check return time of syscall
	epoch = (timeval.tv_sec * ONE_SEC) + timeval.tv_usec;
	return (epoch);
}
