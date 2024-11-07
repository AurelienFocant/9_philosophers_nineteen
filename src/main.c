#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "libft.h"
#include "philosophers.h"

t_context	fn_setup_context(char **argv, pthread_mutex_t *forks)
{
	t_context	context;

	context.nb_of_philo = ft_atoi(argv[1]);
	context.time_to_die = ft_atoi(argv[2]);
	context.time_to_eat = ft_atoi(argv[3]);
	context.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		context.total_nb_of_meals = ft_atoi(argv[5]);
	context.forks = forks;
	return (context);
}

bool	fn_check_args(int argc)
{
	if (argc < 5 || argc > 6)
		return (false);
	return (true);
}

pthread_mutex_t	*fn_init_forks(t_context *context)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * context->nb_of_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < context->nb_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		// check return value of syscall !!!
		i++;
	}
	return (forks);
}

t_philo	*fn_init_philos(t_context *shared_context)
{ 
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * shared_context->nb_of_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < shared_context->nb_of_philo)
	{
		philo[i].id = i;
		philo[i].shared_context = shared_context;
		i++;
	}
	return (philo);
}

void	fn_free_and_exit(pthread_mutex_t *forks, t_philo *philos, char *msg, t_context shared_context)
{
	int	i;
	(void) philos;

	i = 0;
	if (forks)
	{
		while (i < shared_context.nb_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			//free(forks[i]);
			i++;
		}
	}
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

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

void	fn_sleep(t_philo *philo)
{
	printf("philo nb %i is sleeping\n", philo->id);
	usleep(philo->shared_context->time_to_sleep * 1000);
}

void	*thread_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *) philo_arg;
	while (true)
	{
		// eat
		fn_eat(philo);	
		// sleep
		fn_sleep(philo);
		// think
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_context		shared_context;
	t_philo			*philos;
	int				i;

	if (!fn_check_args(argc))
	{
		printf("wrong args\n");
		return (EXIT_FAILURE);
	}
	forks = fn_init_forks(&shared_context);
	if (!forks)
		fn_free_and_exit(NULL, NULL, "malloc on forks failed", shared_context);
	shared_context = fn_setup_context(argv, forks);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		fn_free_and_exit(forks, NULL, "malloc on philos failed", shared_context);
	i = 0;
	while (i < shared_context.nb_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, thread_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < shared_context.nb_of_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
