#ifndef PROTOTYPES_PHILOSOPHERS_H
# define PROTOTYPES_PHILOSOPHERS_H

#include "philosophers.h"

/*----------------  src  ---------------*/
/* File: main.c */
void	fn_join_threads(t_philo *philos);


/*----------------  src/errors_utils  ---------------*/
/* File: args_utils.c */
bool	fn_check_args(int argc, char **argv);
void	fn_destroy_mutexes(t_philo *philos);
void	fn_cleanup_data(t_philo *philos);
void	fn_free_and_exit(char *msg, t_philo *philos);


/*----------------  src/timestamps_utils  ---------------*/
/* File: get_time.c */
void	fn_update_time_last_meal(t_philo *philo);
bool	fn_is_starving(t_philo *philo);
long	fn_get_timestamp(t_philo *philo);
long	fn_get_epoch_in_usec(void);


/*----------------  src/thread_routines  ---------------*/
/* File: eat.c */
void	fn_lock_neighbour_fork(t_philo *philo);
void	fn_lock_own_fork(t_philo *philo);
void	fn_unlock_neighbour_fork(t_philo *philo);
void	fn_unlock_own_fork(t_philo *philo);
void	fn_eat(t_philo *philo);
void	fn_try_to_eat(t_philo *philo);

/* File: sleep.c */
void	fn_sleep(t_philo *philo);
void	fn_think(t_philo philo);

/* File: routines.c */
t_context	*fn_setup_context(char **argv);
void	*thread_routine(void *philo_arg);
t_philo	*fn_init_philos(t_context *shared_context);

/* File: deaths.c */
bool	fn_check_others_death(t_philo *philo);
void	fn_check_own_death(t_philo *philo);
void	fn_check_for_deaths(t_philo *philo);

#endif
