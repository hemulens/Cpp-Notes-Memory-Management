// Exercise: Create a Stack Overflow
// Your task is to create a small program that allocates so much stack memory that an overflow happens. To do this, use a function that allocates some local variable and calls itself recursively. With each new function call, the address of the local variable shall be printed to the console along with the address of a local variable in main which has been allocated before the first function call.

// The output of the program should look like this:


// ...
// 262011: stack bottom : 0x7ffeefbff688, current : 0x7ffeef400704
// 262012: stack bottom : 0x7ffeefbff688, current : 0x7ffeef4006e4
// 262013: stack bottom : 0x7ffeefbff688, current : 0x7ffeef4006c4
// 262014: stack bottom : 0x7ffeefbff688, current : 0x7ffeef4006a4
// 262015: stack bottom : 0x7ffeefbff688, current : 0x7ffeef400684
// 262016: stack bottom : 0x7ffeefbff688, current : 0x7ffeef400664


#include <stdio.h>

int id = 0; 

void MyRecursiveFunc(int &i) {
  int j = 1;
  printf ("%d: stack bottom : %p, current : %p\n",id++, &i, &j);
  MyRecursiveFunc(i);
}

int main() {
  int i = 0; 
  MyRecursiveFunc(i);

  return 0; 
}