#include <stdio.h> 
#include <stdlib.h> 

int main()
{
  // (X) generates a memory leak (?)
  int *m = (int*)malloc(sizeof(int)); 
  m = NULL; 
  printf("address of m: %p, value: %d\n", m, *m);

  // (Y) uses a dangling pointer
  int *n = (int*)malloc(sizeof(int)); 
  free(n);
  *n = 23;
  printf("address of n: %p, value: %d\n", n, *n);

  // (Z) uses an uninitialized pointer (?)
  char *o;
  *o = 'a';
  printf("address of o: %p, value: %d\n", o, *o);

  return 0;
}


// Quiz : Dynamic Memory Management with malloc, calloc, resize and free
// Question 1: Match the code snippets to the respective comments

// Comments:

// 1. uses a dangling pointer
// 2. uses an uninitialized pointer
// 3. generates a memory leak