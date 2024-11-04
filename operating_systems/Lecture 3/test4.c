
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define USE_MUTEX

// Thread properties.
long N_THREADS    = 10;
long N_ITERATIONS = 100000;

// Global variable for sum.
long sum = 0;

#ifdef USE_MUTEX
pthread_mutex_t lock;
#endif

// Thread body.
void *child_thread(void *arg) {

#ifdef USE_MUTEX
  pthread_mutex_lock(&lock);
#endif

  for (long i=0; i<N_ITERATIONS; i++) {
    sum = sum + 1; // sum++; ++sum;
  }

#ifdef USE_MUTEX
  pthread_mutex_unlock(&lock);
#endif

  return NULL;
}

// Main function.
int main(int argc, char **argv) {

  printf("Argument count: %d\n", argc);
  for(int i=0; i<argc; i++)
    printf("Argument[%d]: %s\n", i, argv[i]);

  if (argc == 3) {
    N_THREADS = atol(argv[1]); // strtol is better!
    N_ITERATIONS = atol(argv[2]);
    printf("Use command arguments:  N_THREADS=%ld  N_ITERATIONS=%ld\n", N_THREADS, N_ITERATIONS);
  }
  else {
    printf("Use default values:  N_THREADS=%ld  N_ITERATIONS=%ld\n", N_THREADS, N_ITERATIONS);
  }

  pthread_t threads[N_THREADS];

#ifdef USE_MUTEX
  pthread_mutex_init(&lock, NULL);
#endif

  // Create threads.
  for (long i=0; i<N_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, &child_thread, 
		       NULL) != 0) 
      perror("pthread_create");
  }

  // Join threads.
  for (long i=0; i<N_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0)
      perror("pthread_join");
  }

  printf("RESULTS:\n");
  printf("\t Computed sum   = %ld\n", sum);
  printf("\t Expected sum   = %ld\n", 
	 N_THREADS * N_ITERATIONS);

#ifdef USE_MUTEX
  pthread_mutex_destroy(&lock);
#endif
 
  return 0;
}
