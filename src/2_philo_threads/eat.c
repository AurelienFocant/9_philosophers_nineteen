#include "philosophers.h"

void	fn_lock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(OWN_FORK));
		fn_print_state(philo, "picked up own fork");
		fn_check_for_deaths(philo);
		pthread_mutex_lock(&(LEFT_FORK));
		fn_print_state(philo, "picked up other fork");
	}
	else
	{
		pthread_mutex_lock(&(LEFT_FORK));
		fn_print_state(philo, "picked up other fork");
		fn_check_for_deaths(philo);
		pthread_mutex_lock(&(OWN_FORK));
		fn_print_state(philo, "picked up own fork");
	}
}

void	fn_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(OWN_FORK));
	pthread_mutex_unlock(&(LEFT_FORK));
}

void	fn_eat(t_philo *philo)
{
	long	time_of_meal;
	long	time_now;
	int		time_to_eat;

	fn_print_state(philo, "is eating");
	philo->meals_eaten += 1;
	time_to_eat = philo->shared_context->time_to_eat;
	time_of_meal = fn_get_epoch_in_usec();
	while (true)
	{
		time_now = fn_get_epoch_in_usec();
		if (time_now >= (time_of_meal + time_to_eat))
			break ;
	}
}

void	fn_check_if_satiated(t_philo *philo)
{
	if (philo->meals_eaten == philo->shared_context->total_nb_of_meals)
	{
		philo->is_satiated = true;
		pthread_exit(&(philo->thread));
	}
}

void	fn_try_to_eat(t_philo *philo)
{
	fn_check_for_deaths(philo);
	fn_lock_forks(philo);
	fn_check_for_deaths(philo);
	fn_update_time_last_meal(philo);
	fn_eat(philo);
	fn_unlock_forks(philo);
	fn_check_if_satiated(philo);
}
