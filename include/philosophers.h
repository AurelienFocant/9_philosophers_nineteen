#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include "libft.h"

# define FALSE	0
# define TRUE	1

# define mSEC		1000
# define ONE_SEC	1000000

# define NB_PHILO	philo->shared_context->nb_of_philo
# define PHILO_ZERO	philo->shared_context->philo_zero
# define OWN_FORK	philo->fork
# define LEFT_FORK	((PHILO_ZERO + 1) % NB_PHILO)->fork	

typedef struct s_philo t_philo;

typedef	struct s_context
{
	long			time_of_start;
	pthread_mutex_t	death_mutex;
	int				is_dead[2];
	int				nb_of_philo;
	t_philo			*philo_zero;
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
	long			time_since_last_meal;
	int				meals_eaten;
	t_context		*shared_context;
}	t_philo;

#include "prototypes_philosophers.h"

#endif
