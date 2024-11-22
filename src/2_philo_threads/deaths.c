#include "philosophers.h"

bool	fn_check_others_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared_context->death_mutex));
	if (philo->shared_context->is_dead == true)
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

void	fn_check_for_deaths(t_philo *philo)
{
	if (fn_check_others_death(philo))
	{
		fn_unlock_forks(philo);
		pthread_exit(&(philo->thread));
	}
}
