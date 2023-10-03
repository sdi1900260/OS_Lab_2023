/* thread_create_join.c demonstrates the fork-join pattern using pthreads.
 *
 * Original author: Joel Adams, Calvin College, Fall 2013.
 *
 * Usage: ./thread_create_join
 */

#include <stdio.h>   // printf()
#include <stdlib.h>  // EXIT_FAILURE
#include <pthread.h> // pthread types and functions

void* childGreetings(void * param) { 
   printf("Greetings from the child thread\n");
   return NULL;
}

int main() {
  pthread_t child;                     // struct for child-thread info
                                       // create child thread:
  int res;                             // result of pthread_create()
  res = pthread_create( &child,        //  our handle for it
                        NULL,          //  its attributes 
                        childGreetings,//  the function it should run
                        NULL);         //  args to that function
  if (res != 0) {
    perror("pthread creation failed");
    exit(EXIT_FAILURE);
  }
  printf("Greetings from the parent (main) thread.\n");
  res = pthread_join(child, NULL);       // thread join: wait for child thread to finish
  if (res != 0) {
    perror("pthread join failed");
    exit(EXIT_FAILURE);
  }
  return 0;
}
