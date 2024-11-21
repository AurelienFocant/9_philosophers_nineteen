#include "philosophers.h"

bool	fn_is_philo_dead(t_banshee *banshee, int id)
{
	long	time_now;
	long	time_diff;
	long	time_to_die;

	/* 
	 * time since last meal ---> time_of_last_meal
	 * time diff --> time_since_last_meal
	 */
	time_now = fn_get_epoch_in_usec();
	time_diff = time_now - banshee->philos[id].time_since_last_meal;
	time_to_die = banshee->shared_context->time_to_die * mSEC;
	if (time_diff >= time_to_die)
		return (true);
	return (false);
}

void	fn_keening(t_banshee *banshee, int id)
{
	long	timestamp;

	timestamp = fn_get_timestamp(banshee->philos);
	printf("%lu philo nb %i dead\n", timestamp, id);
}

void	*banshee_routine(void *banshee_arg)
{
	t_banshee	*banshee;
	int			id;

	banshee = (t_banshee *) banshee_arg;
	while (true)
	{
		id = 0;
		while (id < banshee->shared_context->nb_of_philo)
		{
			if (fn_is_philo_dead(banshee, id))
			{
				pthread_mutex_lock(&(banshee->shared_context->death_mutex));
				banshee->shared_context->is_dead[0] = TRUE;
				banshee->shared_context->is_dead[1] = id;
				fn_keening(banshee, id);
				pthread_mutex_unlock(&(banshee->shared_context->death_mutex));
				return (NULL);
			}
			id++;
		}
	}
	return (NULL);
}

void	fn_banshee(t_banshee *banshee, t_philo *philos)
{
	(void) philos;
	pthread_create(&(banshee->thread), NULL, banshee_routine, banshee);
	//check return value of syscall
}
