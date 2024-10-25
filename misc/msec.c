#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

# define FALSE	0
# define TRUE	1

int	main()
{
	struct timeval	timeval;
	unsigned long	time1;
	unsigned long	time2;

	gettimeofday(&timeval, NULL);
	time1 = timeval.tv_usec;
	printf("%lu: usec at the start\n", time1);

	unsigned long	i;
	i = 0;

	gettimeofday(&timeval, NULL);
	time2 = timeval.tv_usec;
	printf("%lu: usec before printing i\n", time2);
	printf("difference is %lu\n", (time2 - time1));

	i++;
	printf("%lu\n", i);

	gettimeofday(&timeval, NULL);
	time1 = timeval.tv_usec;
	printf("%lu: usec before sleeping\n", time1);
	printf("difference is %lu\n", (time1 - time2));

	usleep(200*1000);

	gettimeofday(&timeval, NULL);
	time2 = timeval.tv_usec;
	printf("%lu: usec after sleeping\n", time2);
	printf("difference is %lu\n", (time2 - time1 - 200000));
}
