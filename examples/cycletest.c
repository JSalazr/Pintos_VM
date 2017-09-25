#include <stdio.h>
#include <syscall.h>

int
main (int argc, char **argv)
{
  int c = 0;
  while(c < 10000000000000){
    c++;
    c--;
    c++;
  }
  return EXIT_SUCCESS;
}
