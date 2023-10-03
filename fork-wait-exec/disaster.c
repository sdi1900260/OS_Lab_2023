/* This program puts a fork bomb into an infinite loop. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  char *newargv[3];
  int j;

  newargv[0] = "cat";
  newargv[1] = "f1.txt";
  newargv[2] = NULL;

  j = 0;
  while (j < 4) {
    printf("Process %d - Top of the for loop.  j = %d\n", getpid(), j);
    fflush(stdout);
    if (fork() == 0) {
      (void) execv("cat", newargv);
    } else {
      j++;
    }
  }
  printf("Process %d exiting.\n", getpid());
  return 0;
}
