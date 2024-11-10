#include "philosophers.h"

bool	fn_check_others_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared_context->death_mutex));
	if (philo->shared_context->is_dead[0] == TRUE)
	{
		pthread_mutex_unlock(&(philo->shared_context->death_mutex));
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&(philo->shared_context->death_mutex));
		return (false);
	}
}

void	fn_check_own_death(t_philo *philo)
{
	long	time_now;

	printf("id is %i\n", philo->id);
	time_now = fn_get_epoch_in_usec();
	printf("time since last meal is %lu\n", philo->time_since_last_meal);
	if (time_now - philo->time_since_last_meal >= philo->shared_context->time_to_die * mSEC)
	{
		pthread_mutex_lock(&(philo->shared_context->death_mutex));
		philo->shared_context->is_dead[0] = TRUE;
		philo->shared_context->is_dead[1] = philo->id;
		pthread_mutex_unlock(&(philo->shared_context->death_mutex));
		printf("philo %i is dead\n", philo->id);
		pthread_exit(&(philo->thread));
	}
}

void	fn_check_for_deaths(t_philo *philo)
{
	if (fn_check_others_death(philo))
		pthread_exit(&(philo->thread));
	fn_check_own_death(philo);
}
