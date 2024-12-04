#include "philosophers.h"

void	fn_lock_forks(t_philo *philo)
{
	//if (philo->id == 4)
	//	printf("HEY %i", (PHILOS + ((philo->id + 1) % NB_PHILO))->id);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&(OWN_FORK)))
			printf("YOOO");
		fn_print_state(philo, "picked up own fork");
		if (pthread_mutex_lock(&(LEFT_FORK)))
			printf("YOOO");
		fn_print_state(philo, "picked up other fork");
	}
	else
	{
		usleep(1);
		if (pthread_mutex_lock(&(LEFT_FORK)))
			printf("YOOO");
		fn_print_state(philo, "picked up other fork");
		if (pthread_mutex_lock(&(OWN_FORK)))
			printf("YOOO");
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
	fn_print_state(philo, "is eating");
	philo->meals_eaten += 1;

	/*
	long	time_of_meal;
	long	time_now;
	int		time_to_eat;

	time_to_eat = philo->shared_context->time_to_eat;
	time_of_meal = fn_get_epoch_in_msec();
	while (true)
	{
		time_now = fn_get_epoch_in_msec();
		if (time_now >= (time_of_meal + time_to_eat))
			break ;
	}
	*/
	fn_wrapper_usleep(philo->shared_context->time_to_eat);
}

void	fn_check_if_satiated(t_philo *philo)
{
	if (philo->meals_eaten == philo->shared_context->total_nb_of_meals)
	{
		pthread_mutex_lock(&(philo->shared_context->satiation_mutex));
		philo->is_satiated = true;
		philo->shared_context->nb_of_philos_satiated++;
		pthread_mutex_unlock(&(philo->shared_context->satiation_mutex));
		fn_unlock_forks(philo);
		pthread_exit(&(philo->thread));
	}
}

void	fn_try_to_eat(t_philo *philo)
{
	fn_lock_forks(philo);
	fn_update_time_last_meal(philo);
	fn_eat(philo);
	fn_unlock_forks(philo);
	fn_check_if_satiated(philo);
}
