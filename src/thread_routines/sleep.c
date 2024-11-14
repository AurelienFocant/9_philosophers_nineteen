#include "philosophers.h"

void	fn_sleep(t_philo *philo)
{
	fn_print_state(philo, "is sleeping");
	usleep(philo->shared_context->time_to_sleep * mSEC);
}

// WRONG ! Thinking is the state where a philo is waiting to eat !
/*
void	fn_think(t_philo philo)
{
	while (true)
	{
		if (time.now >= time.start + (1 * ONE_SEC))
				break;
	}
}
*/
