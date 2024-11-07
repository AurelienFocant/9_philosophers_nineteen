#include "philosophers.h"

void	fn_eat(t_philo *philo)
{
	int	id;
	int	nb_of_philo;
	pthread_mutex_t	*forks;

	id = philo->id;
	nb_of_philo = philo->shared_context->nb_of_philo;
	forks = philo->shared_context->forks;
	if (id % 2)
	{
		pthread_mutex_lock(&(forks[(id + 1) %nb_of_philo]));
		printf("philo nb %i picked left fork\n", id);
	}
	else
	{
		pthread_mutex_lock(&(forks[(id + nb_of_philo - 1) % nb_of_philo]));
		printf("philo nb %i picked right fork\n", id);
	}
	pthread_mutex_lock(&(forks[id]));
	printf("philo nb %i picked own fork\n", id);
	printf("philo nb %i is eatin\n", id);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&(forks[(id + 1) % nb_of_philo]));
		printf("philo nb %i picked left fork\n", id);
	}
	else
	{
		pthread_mutex_unlock(&(forks[(id + nb_of_philo - 1) % nb_of_philo]));
		printf("philo nb %i picked right fork\n", id);
	}
	pthread_mutex_unlock(&(philo->shared_context->forks[id]));
}
