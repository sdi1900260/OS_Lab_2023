/* This program calls execv() rather than execvp(), and this is a fork bomb.
   You won't see the fork bomb, though, because the exponential blowup is small,
   and nothing is printed. */

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
    if (fork() == 0) {
      (void) execv("cat", newargv);
    } else {
      wait(&status);
    }
  }
  return 0;
}
