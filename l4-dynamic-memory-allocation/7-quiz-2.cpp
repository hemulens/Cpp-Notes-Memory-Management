#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>

int *f1(void)
{
  int x = 10;
  return (&x);  // warning: address of stack memory associated with local variable 'x' returned
}

int *f2(void)
{
  int *px;  // we must initialize a poiner and allocate memory first
  *px = 10;  // segmentation fault 11
  return px;
}

int *f3(void)
{
  int *px;
  px = (int *)malloc(sizeof(int));
  *px = 10;
  return px;
}

int main() {
  std::cout << f3() << std::endl;
}


// Which of the functions above is likely to cause pointer-related problems?


// Great work! In f1, the pointer variable x is a local variable to f1, and f1 returns the pointer to that variable. x can disappear after f1() is returned if x exists on the stack. So &x can become invalid.

// In f2, the pointer variable px is assigned a value without allocating its space.

// f3 works fine. Memory is allocated to the pointer variable px using malloc(). So, px exists on the heap, its existence will remain in memory even after the return of f3() as it is on the heap.