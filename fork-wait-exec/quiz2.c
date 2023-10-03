/*
How many times is wait() called?  (too few/too many/just enough)
What is the outcome? (never end/finish ok/segfault)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int i, status;

  for (i = 0; i < 3; i++) fork();
  for (i = 0; i < 3; i++) wait(&status); // added line
  printf("Process %d exiting.\n", getpid());
  return 0;
}
