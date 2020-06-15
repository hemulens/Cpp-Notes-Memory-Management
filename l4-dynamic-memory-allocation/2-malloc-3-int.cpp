#include <stdio.h> 
#include <stdlib.h> // for malloc
  
int main() 
{ 
  // void *p = malloc(sizeof(int));   // this won't work
  int *p1 = (int*)malloc(sizeof(int)); // do not rely on pre-initialization
  int *p2 = (int*)malloc(3*sizeof(int));
  
  printf("address=%p, value=%d\n", p1, *p1);
  printf("address=%p, value=%d\n", p2, *p2);

  return 0; 
}