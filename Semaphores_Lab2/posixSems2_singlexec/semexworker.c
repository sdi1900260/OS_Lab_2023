#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define TEN_MILLION 10000000L
#define BUFSIZE 1024

void worker(int i, void * args)
{
   char buffer[BUFSIZE];
   char *c;
   sem_t *semlockp;
   struct timespec sleeptime;

   semlockp = (sem_t *)args;
   sleeptime.tv_sec = 0;
   sleeptime.tv_nsec = 100000000L;
   snprintf(buffer, BUFSIZE, "This is process %ld\n", (long)getpid());
   c = buffer;
   setbuf(stderr, NULL);  // specify no buffering for stderr

   /****************** entry section *******************************/

   while (sem_wait(semlockp) == -1)        /* Entry section */
      if(errno != EINTR) {
         fprintf(stderr, "Process failed to lock semaphore\n");
         return;
      }

   /****************** start of critical section *******************/

   while (*c != '\0') {
      fputc(*c, stderr); // no buffering: output each synchronously
      c++;
      nanosleep(&sleeptime, NULL);
   }

   /****************** exit section ********************************/

   if (sem_post(semlockp) == -1) {        /* Exit section */
      fprintf(stderr, "Process failed to unlock semaphore\n");
   }
   /****************** remainder section ***************************/
   return;
}
