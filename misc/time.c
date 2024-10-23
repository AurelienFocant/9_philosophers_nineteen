#include <sys/time.h>
#include <stdio.h>

# define FALSE	0
# define TRUE	1

int	main()
{
	struct timeval	timeval;
	unsigned long	time_start;
	unsigned long	time_end;

	gettimeofday(&timeval, NULL);
	time_start = timeval.tv_sec;
	printf("%lu\n", time_start);

	unsigned long	i;
	i = 0;
	while (TRUE)
	{
		gettimeofday(&timeval, NULL);
		time_end = timeval.tv_sec;
		i++;
		if (time_end > (time_start + 1))
			break;
	}
	printf("%lu\n", i);
	printf("%lu\n", time_end);
}
