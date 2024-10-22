#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef	struct s_context
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals;
}	t_context;

typedef struct s_philo
{
	t_context	*context;
}	t_philo;

#endif
