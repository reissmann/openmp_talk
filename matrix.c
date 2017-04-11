/* Matrix multiplication example with OpenMP. Work-sharing using omp for 
 * and omp sections. You can play with matrix sizes to see the effects
 * of parallelization.
 *
 * Compile either single-threaded (without OpenMP)
 *   gcc -Wall -o hello_omp hello_omp.c
 * or multi-threaded (with OpenMP)
 *   gcc -Wall -fopenmp -o hello_omp hello_omp.c
 *
 * When you compile this program using OpenMP, by default it will create
 * as many threads as there are cores in your computer. You can, however,
 * set an environment variable to control the number of threads that should
 * be created. To test this behavior, run
 *
 *  export OMP_NUM_THREADS=2
 *  ./matrix
 *  unset OMP_NUM_THREADS
 *
 * Note: Depending on your operating system, the definition of environment
 *       variabled may differ from the example.
 *
 * Sven Reissmann <sven.reissmann@rz.hs-fulda.de>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
  #include <omp.h>
#endif

#define P 32
#define Q 32
#define R 32

#define PRINT 0

int main (int argc, char *argv[]) 
{
  int tid, nthreads, chunk;	  /* Thread control variables */
  int i, j, k;			  /* Loop variables */
  static long int a[P][Q],	  /* Source matrix a */
                  b[Q][R],	  /* Source matrix b */
                  c[P][R];	  /* Result matrix c */
  time_t  start_wall, end_wall;   /* start/end time (wall clock)  */
  clock_t cpu_time;               /* used cpu time                */
  
  tid = 0;
  nthreads = 1;
  chunk = 10;
  
  start_wall = time (NULL);
  cpu_time   = clock ();

  #pragma omp parallel default (none) \
    shared (a, b, c, nthreads, chunk) private (tid, i, j, k)
  {
    #ifdef _OPENMP
      tid = omp_get_thread_num ();
    #endif
  
    /* Get number of threads and print a header (only once) */
    #pragma omp single
    {
      #ifdef _OPENMP
        nthreads = omp_get_num_threads ();
      #endif
      printf ("Thread %d: Running with %d threads\n", tid, nthreads);
      printf ("Thread %d: Initializing matrices ...\n", tid);
    }
  
    /* Initialization of source matrices using sections.
     * Two threads from the team will be picked to initialize
     * one of the source matrices each.
     */
    #pragma omp sections
    {
      #pragma omp section
      {
        printf ("Thread %d: Initializing matrix a\n", tid);
        for (i = 0; i < P; i++)
        {
          for (j = 0; j < Q; j++)
          {
            a[i][j] = i + j;
          }
        }
      }
  
      #pragma omp section
      {
        printf ("Thread %d: Initializing matrix b\n", tid);
        for (i = 0; i < Q; i++)
        {
          for (j = 0; j < R; j++)
          {
            b[i][j] = i * j;
          }
        }
      }
    }

    /* Matrix multiplication using for work-sharing construct.
     * Work sharing happens on the outer loop only.
     */
    printf ("Thread %d: Starting matrix multiplication ...\n", tid);
    #pragma omp for schedule (static, chunk)
    for (i = 0; i < P; i++)    
    {
      printf ("Thread %d: Calculating row %d\n", tid, i);
      for (j = 0; j < Q; j++)
      {
        for (k = 0; k < R; k++)
        {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }

  }

  end_wall = time (NULL);
  cpu_time = clock () - cpu_time;
  
  /* Print results */
  #if (PRINT == 1)
  printf ("Result Matrix:\n");
  for (i = 0; i < P; i++)
  {
    for (j = 0; j < R; j++)
    {
      printf ("%12ld", c[i][j]);
    }
    printf("\n"); 
  }
  #endif

  printf ("elapsed time      cpu time\n"
          "    %6.2f s      %6.2f s\n",
          difftime (end_wall, start_wall),
          (double) cpu_time / CLOCKS_PER_SEC);

}

