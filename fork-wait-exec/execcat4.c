/* This program exits when execv() fails -- no more fork bomb! */

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
      perror("execcat4's execv call");
      exit(1);
    } else {
      wait(&status);
    }
  }
  printf("Process %d exiting.\n", getpid());
  return 0;
}
