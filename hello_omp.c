/* A simple hello world program, which uses OpenMP to parallize the output
 * of the text "Hello, world."
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
 *  ./hello_omp
 *  unset OMP_NUM_THREADS
 *
 * Note: Depending on your operating system, the definition of environment
 *       variabled may differ from the example.
 *
 * Author: Sven Reissmann <sven.reissmann@rz.hs-fulda.de> 
 */

#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    #pragma omp parallel
    printf("Hello, world.\n");
    return EXIT_SUCCESS;
}

