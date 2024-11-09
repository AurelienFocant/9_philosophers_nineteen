#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "libft.h"

# define FALSE	0
# define TRUE	1

# define ONE_SEC	1000

# define NB_PHILO	philo->shared_context->nb_of_philo
# define FORKS		philo->shared_context->forks
# define ID			philo->id
# define OWN_FORK	FORKS[ID]
# define LEFT_FORK	FORKS[(ID + 1) % NB_PHILO]
# define RIGHT_FORK	FORKS[(ID + NB_PHILO - 1) % NB_PHILO]

typedef	struct s_context
{
	int	is_dead[2];
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	total_nb_of_meals;
	pthread_mutex_t	*forks;
}	t_context;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_context		*shared_context;
}	t_philo;

#include "prototypes_philosophers.h"

#endif
