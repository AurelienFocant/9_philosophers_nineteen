#include "philosophers.h"

void	fn_update_time_last_meal(t_philo *philo)
{
	philo->time_of_last_meal = fn_get_epoch_in_usec();
}

long	fn_get_timestamp(t_philo *philo, int mode)
{
	long	timestamp;

	timestamp = fn_get_epoch_in_usec() - philo->shared_context->time_of_start;
	if (mode == PHILO)
		fn_check_for_deaths(philo);
	return (timestamp / mSEC);
}

long	fn_get_epoch_in_usec(void)
{
	struct timeval	timeval;
	long			epoch;

	gettimeofday(&timeval, NULL);
	epoch = (timeval.tv_sec * ONE_SEC) + timeval.tv_usec;
	return (epoch);
}
