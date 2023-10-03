/* thread_create_join2.c demonstrates the fork-join pattern using pthreads;
 *  the desired number of threads is passed as a commandline arg.
 *
 * Original author: Joel Adams, Calvin College, Fall 2013.
 *
 * Usage: ./thread_create_join2 [numThreads]
 */

#include <stdio.h>   // printf()
#include <stdlib.h>  // atoi(), exit(), ...
#include <pthread.h> // pthread types and functions

void* childGreetings(void * id) { 
   unsigned long childID = (unsigned long) id;
   printf("Greetings from child #%lu\n", childID);
   return NULL;
}

unsigned long processCommandLine(int argc, char** argv) {
   if (argc == 2) {
      return strtoul(argv[1], 0, 10);
   } else if (argc == 1) {
      return 1;
   } else {
      fprintf(stderr, "\nUsage: %s [numThreads]\n", argv[0]);
      exit(1);
   }
}

int main(int argc, char** argv) {
   pthread_t * children;                   // dynamic array of child threads
   unsigned long id = 0;                   // loop control variable
   unsigned long numThreads = 0;           // desired # of threads
                                             // get desired # of threads
   numThreads = processCommandLine(argc, argv);
                                             // allocate array of handles
   children = malloc( numThreads * sizeof(pthread_t) );
                                             // create thread:
   for (id = 1; id < numThreads; id++) {
      int res;                               // result of pthread_create()
      res = pthread_create(&(children[id-1]),  // our handle for the child 
                           NULL,               // attributes of the child
                           childGreetings,     // the function it should run
                           (void*) id);       // args to that function
      if (res != 0) {
         perror("Thread creation failed");
         exit(EXIT_FAILURE);
      }
   }

   for (id = 1; id < numThreads; id++) {   // thread join:
      if (pthread_join( children[id-1], NULL) != 0) {
         perror("Thread join failed");
         exit(EXIT_FAILURE);
      }
   }
   printf("Greetings from the parent, thread #0.\n");
   free(children);                         // deallocate array
   return 0;
}
