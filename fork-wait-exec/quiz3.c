/*
If the program is compiled into a.out and called as
a) ./a.out 2 4
b) ./a.out 4 2
c) ./a.out 2 2

What will happen to the parent? (zombie/orphan/neither/undetermined)
What will happen to the child? (zombie/orphan/neither/undetermined)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int t;

  t = (fork() == 0) ? atoi(argv[1]) : atoi(argv[2]) ;
  sleep(t);
  return 0;
}
