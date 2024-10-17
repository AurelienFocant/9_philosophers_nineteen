#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int	common = 162;
pthread_mutex_t	mutex;

void	*threadfun(void *threadid)
{
	long	tid;

	tid = (long) threadid;
	pthread_mutex_lock(&mutex);
	printf("Thread #%lx stack: %lx common data: %lx (%d)\n", tid, (unsigned long) &tid, (unsigned long) &common, common++);
	pthread_mutex_unlock(&mutex);
	printf("Mutex address is %p\n", &mutex);
	for (int i = 0; i < 100; i++) {
		pthread_mutex_lock(&mutex);
		printf("%i\n", i);
		printf("%i\n", common++);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	long		t;
	int			nb_threads;
	pthread_t	*threads;
	int			rc;

	pthread_mutex_init(&mutex, NULL);
	printf("Mutex address is %p\n", &mutex);
	nb_threads = 5;
	if (argc > 1) {
		nb_threads = atoi(argv[1]);
	}
	threads = malloc(sizeof(pthread_t) * nb_threads);
	printf("Main stack: %lx, common data: %lx (%i)\n", (unsigned long) &t, (unsigned long) &common, common);
	t = 0;
	while (t < nb_threads) {
		rc = pthread_create(&threads[t], NULL, threadfun, (void *) t);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %i\n", rc);
			exit(EXIT_FAILURE);
		}
		t++;
	}
	t = 0;
	while (t < nb_threads) {
		pthread_join(threads[t], NULL);
		t++;
	}
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}

/* COMMENT
*/
