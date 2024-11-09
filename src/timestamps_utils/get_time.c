#include "philosophers.h"

long	fn_get_epoch_in_usec(void)
{
	struct timeval	timeval;
	long			epoch;

	gettimeofday(&timeval, NULL);
	// check return time of syscall
	epoch = (timeval.tv_sec * ONE_SEC) + timeval.tv_usec;
	printf("%lu\n", epoch);
	return (epoch);
}
