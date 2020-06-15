#include <stdio.h>

int main() {
  int a;
  int b = a * 42;  // can't perfoem the operation with uninitialized a
  printf("%d \n",b);
}


// Uninitialized Memory Depending on the C++ compiler, data structures are sometimes initialized (most often to zero) and sometimes not. So when allocating memory on the heap without proper initialization, it might sometimes contain garbage that can cause problems.

// Generally, a variable will be automatically initialized in these cases:

// it is a class instance where the default constructor initializes all primitive types
// array initializer syntax is used, such as int a[10] = {}
// it is a global or extern variable
// it is defined static
// The behavior of the following code is potentially undefined:

// int a;
// int b=a*42;
// printf("%d",b);