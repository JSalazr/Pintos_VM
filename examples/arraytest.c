#include <stdio.h>
#include <syscall.h>

int
main (int argc, char **argv)
{
  int arr[10000];
  for(int c = 0; c < 10000; c++){
    arr[c] = 0;
    printf("%d\n", arr[c]);
  }
  printf("Termino de recorrer\n");

  return EXIT_SUCCESS;
}
