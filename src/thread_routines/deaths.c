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
	if (time_now - philo->time_since_last_meal >= philo->shared_context->time_to_die)
	{
		pthread_mutex_lock(&(philo->shared_context->death_mutex));
		philo->shared_context->is_dead[0] = TRUE;
		philo->shared_context->is_dead[1] = philo->id;
		pthread_mutex_unlock(&(philo->shared_context->death_mutex));
	}
}

void	fn_check_deaths(t_philo *philo)
{
	if (fn_check_others_death(philo))
		pthread_exit(&(philo->thread));
	fn_check_own_death(philo);
}