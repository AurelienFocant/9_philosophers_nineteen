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
	fn_check_for_deaths(philo);
	fn_lock_neighbour_fork(philo);
	fn_check_for_deaths(philo);
	fn_lock_own_fork(philo);
	printf("philo nb %i is eatin\n", philo->id);
	fn_check_for_deaths(philo);
	fn_unlock_neighbour_fork(philo);
	fn_check_for_deaths(philo);
	fn_unlock_own_fork(philo);
}
