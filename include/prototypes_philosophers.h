#ifndef PROTOTYPES_PHILOSOPHERS_H
# define PROTOTYPES_PHILOSOPHERS_H

# include "philosophers.h"

/*----------------  main.c  ---------------*/

/*----------------  args_utils.c  ---------------*/
bool	fn_check_args(int argc);
void	fn_free_and_exit(pthread_mutex_t *forks, t_philo *philos, char *msg, t_context shared_context);

/*----------------  eat.c  ---------------*/
void	fn_lock_neighbour_fork(t_philo *philo);
void	fn_lock_own_fork(t_philo *philo);
void	fn_unlock_neighbour_fork(t_philo *philo);
void	fn_unlock_own_fork(t_philo *philo);
void	fn_eat(t_philo *philo);

/*----------------  sleep.c  ---------------*/
void	fn_sleep(t_philo *philo);
void	fn_think(t_philo philo);

/*----------------  routines.c  ---------------*/
t_context	fn_setup_context(char **argv, pthread_mutex_t *forks);
pthread_mutex_t	*fn_init_forks(t_context *context);
t_philo	*fn_init_philos(t_context *shared_context);
void	*thread_routine(void *philo_arg);

#endif
