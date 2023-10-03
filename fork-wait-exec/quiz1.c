/*
How many lines will it print? Hint: every process created prints one line before it exits?
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int i;

  for (i = 0; i < 3; i++) fork();
  printf("Process %d exiting.\n", getpid());
  return 0;
}
