#include "philosophers.h"

bool	fn_is_philo_dead(t_banshee *banshee, int id)
{
	long	time_now;
	long	time_since_last_meal;
	long	time_to_die;

	if (banshee->philos[id].is_satiated)
		return(false);
	time_now = fn_get_epoch_in_usec();
	time_since_last_meal = time_now - banshee->philos[id].time_of_last_meal;
	time_to_die = banshee->shared_context->time_to_die * mSEC;
	if (time_since_last_meal >= time_to_die)
		return (true);
	return (false);
}

void	fn_keening(t_banshee *banshee, int id)
{
	long	timestamp;

	pthread_mutex_lock(&(banshee->shared_context->death_mutex));
	banshee->shared_context->is_dead = true;
	pthread_mutex_unlock(&(banshee->shared_context->death_mutex));
	timestamp = fn_get_timestamp_banshee(banshee->philos);
	printf("%lu philo nb %i DEAD!!!!!!!!!!!\n", timestamp, id);
}

bool	fn_all_satiated(t_banshee *banshee)
{
	int	id;

	id = 0;
	while (id < banshee->shared_context->nb_of_philo)
	{
		if (!banshee->philos[id].is_satiated)
			return (false);
		id++;
	}
	return (true);
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
			if (fn_all_satiated(banshee))
				return (NULL);
			if (fn_is_philo_dead(banshee, id))
			{
				fn_keening(banshee, id);
				return (NULL);
			}
			id++;
		}
	}
	return (NULL);
}

bool	fn_banshee_start_thread( t_banshee *banshee, t_context *shared_context, t_philo *philos)
{
	banshee->shared_context = shared_context;
	banshee->philos = philos;
	if (pthread_create
			(&(banshee->thread), NULL, banshee_routine, banshee)
			!= EXIT_SUCCESS)
	{
		return (false);
	}
	return (true);
}
