/* This program runs the "cat" program four times by calling fork() in a for loop.
   Inside the loop, the child calls execvp("cat"), and the parent calls wait(). 

   Although this program runs fine, it will turn into a fork bomb if there's a bug. */

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
      (void) execvp("cat", newargv);
    } else {
      wait(&status);
    }
  }
  return 0;
}
