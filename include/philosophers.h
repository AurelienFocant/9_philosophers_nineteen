#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include "libft.h"

# define mSEC		1000
# define ONE_SEC	1000000

# define PHILO		0
# define BANSHEE	1

# define NB_PHILO	philo->shared_context->nb_of_philos
# define PHILOS		philo->shared_context->philos
# define OWN_FORK	philo->fork
# define LEFT_FORK	(PHILOS + ((philo->id + 1) % NB_PHILO))->fork

typedef struct s_philo t_philo;

typedef	struct s_context
{
	long			time_of_start;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	bool			is_dead;
	int				nb_of_philos;
	t_philo			*philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_nb_of_meals;
}	t_context;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	fork;
	long			time_of_last_meal;
	int				meals_eaten;
	bool			is_satiated;
	t_context		*shared_context;
}	t_philo;

typedef struct s_banshee
{
	pthread_t	thread;
	t_philo		*philos;
	t_context	*shared_context;
}	t_banshee;

#include "prototypes_philosophers.h"

#endif
