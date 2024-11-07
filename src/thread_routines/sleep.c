#include "philosophers.h"

void	fn_sleep(t_philo *philo)
{
	printf("philo nb %i is sleeping\n", philo->id);
	usleep(philo->shared_context->time_to_sleep * 1000);
}
