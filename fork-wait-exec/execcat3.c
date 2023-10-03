/* This has the same fork bomb as execcat2.c, but we're printing stuff out so
   that you can see it. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  char *newargv[3];
  int status, j;

  newargv[0] = "cat";
  newargv[1] = "f1.txt";
  newargv[2] = NULL;

  for (j = 0; j < 4; j++) {
    printf("Process %d - Top of the for loop.  j = %d\n", getpid(), j);
    fflush(stdout);
    if (fork() == 0) {
      (void) execv("cat", newargv);
    } else {
      wait(&status);
    }
  }
  printf("Process %d exiting.\n", getpid());
  return 0;
}
