#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef	struct s_context
{
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

#endif
