#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_context	shared_context;
	t_philo		*philos;
	t_banshee	*banshee;

	if (!fn_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!fn_setup_context(&shared_context, argv))
		return (EXIT_FAILURE);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		return (EXIT_FAILURE);
	banshee = fn_init_banshee(&shared_context, philos);
	fn_banshee(banshee, philos);
	fn_philos_start_meal(philos);
	fn_join_threads(banshee, philos);
	fn_cleanup_data(philos);
	return (EXIT_SUCCESS);
}
