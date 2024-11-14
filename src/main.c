#include "philosophers.h"

void	fn_join_threads(t_philo *philos)
{
	int	id;

	id = 0;
	while (id < philos->shared_context->nb_of_philo)
	{
		pthread_join(philos[id].thread, NULL);
		id++;
	}
}

void	fn_philos_start_meal(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philo[0]->shared_context->nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, philos_routine, &philos[i]);
		i++;
	}
}

void	fn_keening(int	id)
{
	long	timestamp;

	timestamp = fn_get_timestamp(philo);
	printf("%lu philo nb %i dead\n", timestamp, philo->id);
}

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
	time_diff = time_now - banshee->philos[id]->time_since_last_meal;
	time_to_die = philo->shared_context->time_to_die * mSEC;
	if (time_diff >= time_to_die)
		return (true);
	return (false);
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
				fn_keening(id);
				pthread_mutex_unlock(&(banshee->shared_context->death_mutex));
				return (NULL);
			}
			id++;
		}
	}
	return (NULL);
}

fn_banshee(t_philo *philos)
{
	t_banshee	banshee;

	pthread_create(&(banshee.thread), NULL, banshee_routine, &banshee);
	//check return value of syscall
}

int	main(int argc, char **argv)
{
	t_context		shared_context;
	t_philo			*philos;

	if (!fn_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!fn_setup_context(&shared_context, argv))
		return (EXIT_FAILURE);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		return (EXIT_FAILURE);
	fn_banshee(philos);
	fn_philos_start_meal(philos);
	fn_join_threads(philos);
	fn_cleanup_data(philos);
	return (EXIT_SUCCESS);
}
