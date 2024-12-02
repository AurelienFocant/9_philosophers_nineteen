#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_context	shared_context;
	t_banshee	banshee;
	t_philo		*philos;

	if (!fn_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!fn_setup_context(&shared_context, argv))
		return (EXIT_FAILURE);
	philos = fn_init_philos(&shared_context);
	if (!philos)
		return (EXIT_FAILURE);
	if (!fn_banshee_start_thread(&banshee, &shared_context, philos))
	{
		fn_cleanup_data(philos);
		return (EXIT_FAILURE);
	}
	if (!fn_philos_start_threads(philos))
	{
		fn_cleanup_data(philos);
		return (EXIT_FAILURE);
	}
	fn_join_threads(&banshee, philos);
	fn_cleanup_data(philos);
	return (EXIT_SUCCESS);
}
