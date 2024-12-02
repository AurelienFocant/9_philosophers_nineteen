#include "philosophers.h"

bool	fn_is_philo_dead(t_banshee *banshee)
{
	long	time_now;
	long	time_since_last_meal;
	long	time_to_die;
	int		id;

	id = 0;
	while (id < banshee->shared_context->nb_of_philos)
	{
		if (banshee->philos[id].is_satiated)
			continue;
		time_now = fn_get_epoch_in_usec();
		time_since_last_meal = time_now - banshee->philos[id].time_of_last_meal;
		time_to_die = banshee->shared_context->time_to_die;
		if (time_since_last_meal >= time_to_die)
		{
			fn_keening(banshee, id, time_now);
			return (true);
		}
		id++;
	}
	return (false);
}

void	fn_keening(t_banshee *banshee, int id, long timestamp)
{
	//long	timestamp;

	pthread_mutex_lock(&(banshee->shared_context->death_mutex));
	banshee->shared_context->is_dead = true;
	pthread_mutex_unlock(&(banshee->shared_context->death_mutex));
	//timestamp = fn_get_timestamp(banshee->philos, BANSHEE);
	printf("%lu %i died\n", timestamp - banshee->shared_context->time_of_start, id);
}

bool	fn_all_satiated(t_banshee *banshee)
{
	int	id;

	id = 0;
	while (id < banshee->shared_context->nb_of_philos)
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

	banshee = (t_banshee *) banshee_arg;
	while (true)
	{
		if (fn_is_philo_dead(banshee))
			return (NULL);
		if (fn_all_satiated(banshee))
			return (NULL);
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
