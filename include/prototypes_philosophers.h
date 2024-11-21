#ifndef PROTOTYPES_PHILOSOPHERS_H
# define PROTOTYPES_PHILOSOPHERS_H

#include "philosophers.h"

/*----------------  src/banshee_thread  ---------------*/
/* File: banshee.c */
bool	fn_is_philo_dead(t_banshee *banshee, int id);
void	fn_keening(t_banshee *banshee, int id);
void	*banshee_routine(void *banshee_arg);
bool	fn_banshee_start_thread(t_banshee *banshee, t_context *shared_context, t_philo *philos);

/* File: deaths.c */
bool	fn_check_others_death(t_philo *philo);
void	fn_check_own_death(t_philo *philo);
void	fn_check_for_deaths(t_philo *philo);


/*----------------  src/general_utils  ---------------*/
/* File: init.c */
bool	fn_check_args(int argc, char **argv);
bool	fn_setup_context(t_context *context, char **argv);
t_philo	*fn_init_philos(t_context *shared_context);

/* File: cleanup.c */
void	fn_destroy_mutexes(t_philo *philo);
void	fn_cleanup_data(t_philo *philos);
void	fn_free_and_exit(char *msg, t_philo *philos);
void	fn_join_threads(t_banshee *banshee, t_philo *philos);


/*----------------  src  ---------------*/
/* File: main.c */


/*----------------  src/philo_threads  ---------------*/
/* File: eat.c */
void	fn_eat(t_philo *philo);
void	fn_print_state(t_philo *philo, char *msg);
void	fn_lock_forks(t_philo *philo);
void	fn_unlock_forks(t_philo *philo);
void	fn_try_to_eat(t_philo *philo);

/* File: philos.c */
void	fn_sleep(t_philo *philo);
void	*philos_routine(void *philo_arg);
bool	fn_philos_start_threads(t_philo *philos);


/*----------------  src/timestamps_utils  ---------------*/
/* File: get_time.c */
void	fn_update_time_last_meal(t_philo *philo);
bool	fn_is_starving(t_philo *philo);
long	fn_get_timestamp(t_philo *philo);
long	fn_get_epoch_in_usec(void);

#endif
