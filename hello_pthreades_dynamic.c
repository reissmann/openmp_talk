/* A simple hello world program, which uses pthreads to parallize the
 * output of the text "Hello, world."
 *
 * Compile with
 *   gcc -Wall -lpthread -o hello_pthreads_dynamic hello_pthreads_dynamic.c
 *
 * This program will create as many threads as specified by the constant
 * NUM_THREADS. You can, however, overwrite that constant by specifying a
 * command-line parameter. To test this behavior, run
 *
 *  ./hello_pthreads_dynamic
 *  ./hello_pthreads_dynamic 2
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
int main (int argc, char **argv)
{
  int i, num;
  pthread_t *t;

  /* Get number of threads from cli
   */
  num = NUM_THREADS;
  if (argc == 2)
  {
    num = atoi (argv[1]);
  }

  /* Now that we know how many threads to create, we can reserve
   * memory for the threads control datastructure
   */
  t = (pthread_t *) malloc (num * sizeof (pthread_t));

  /* Create the threads
   */
  for (i = 0; i < num; ++i)
  {
    pthread_create (&t[i], NULL, pprint, NULL);
  }

  /* Join the threads
   */
  for (i = 0; i < num; ++i)
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
  printf ("Hello, world.\n");
  pthread_exit (EXIT_SUCCESS);
}

