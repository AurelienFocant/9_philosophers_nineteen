#include "philosophers.h"

void	fn_update_time_last_meal(t_philo *philo)
{
	philo->time_of_last_meal = fn_get_epoch_in_msec();
}

long	fn_get_timestamp(t_philo *philo, int mode)
{
	long	timestamp;

	timestamp = fn_get_epoch_in_msec() - philo->shared_context->time_of_start;
	if (mode == PHILO)
		fn_check_for_deaths(philo);
	return (timestamp);
}

long	fn_get_epoch_in_msec(void)
{
	struct timeval	timeval;
	long			epoch;

	gettimeofday(&timeval, NULL);
	epoch = (timeval.tv_sec * 1000) + timeval.tv_usec / 1000;
	return (epoch);
}
