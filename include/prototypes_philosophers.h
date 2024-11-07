#ifndef PROTOTYPES_PHILOSOPHERS_H
# define PROTOTYPES_PHILOSOPHERS_H

#include "philosophers.h"

/*----------------  src  ---------------*/
/* File: main.c */


/*----------------  src/errors_utils  ---------------*/
/* File: args_utils.c */
bool	fn_check_args(int argc);
void	fn_free_and_exit(pthread_mutex_t *forks, t_philo *philos, char *msg, t_context shared_context);


/*----------------  src/thread_routines  ---------------*/
/* File: eat.c */
void	fn_eat(t_philo *philo);

/* File: sleep.c */
void	fn_sleep(t_philo *philo);

/* File: routines.c */
t_context	fn_setup_context(char **argv, pthread_mutex_t *forks);
pthread_mutex_t	*fn_init_forks(t_context *context);
t_philo	*fn_init_philos(t_context *shared_context);
void	*thread_routine(void *philo_arg);

#endif
