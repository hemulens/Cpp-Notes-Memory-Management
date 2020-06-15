#include <stdio.h> 
#include <stdlib.h> // for malloc
#include <iostream>  

int main() 
{ 
  int *p = (int*)malloc(3*sizeof(int));
  p[0] = 1; p[1] = 2; p[2] = 3;
  printf("address=%p, second value=%d\n", p, p[1]);

  std::cout << &p[1] << std::endl;
  return 0; 
}

// Memory for Arrays and Structs
// Since arrays and pointers are displayed and processed identically internally, individual blocks of data can also be accessed using array syntax:


//     int *p = (int*)malloc(3*sizeof(int));
//     p[0] = 1; p[1] = 2; p[2] = 3;
//     printf("address=%p, second value=%d\n", p, p[1]);