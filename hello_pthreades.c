/* A simple hello world program, which uses pthreads to parallize the
 * output of the text "Hello, world."
 *
 * Compile with
 *   gcc -Wall -lpthread -o hello_pthreads hello_pthreads.c
 *
 * This program will create as many threads as specified by the constant
 * NUM_THREADS. The number of threads is fixed and cannot be changed
 * without recompiling the program.
 *
 * To test, run
 *  ./hello_pthreads
 *
 * Author: Sven Reissmann <sven.reissmann@rz.hs-fulda.de> 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

void *pprint (void *);


/* Create some threads, let them do their work, join them and exit.
 */
int main (void)
{
  int i;
  pthread_t t[NUM_THREADS];

  /* Create the threads 						*/
  for (i = 0; i < NUM_THREADS; ++i)
  {
    pthread_create (&t[i], NULL, pprint, NULL);
  }

  /* Join the threads							*/
  for (i = 0; i < NUM_THREADS; ++i)
  {
    pthread_join (t[i], NULL);
  }

  return EXIT_SUCCESS;
}


/* This function runs as a pthread and will print the text "Hello, world."
 * to stdout (i.e., your screen).
 */
void *pprint (void *arg)
{
  printf("Hello, world.\n");
  pthread_exit (EXIT_SUCCESS);
}

