#include <stdio.h>
#include <cstring>

int main() {
  char *pStr = new char[25];
  delete[] pStr;
  strcpy(pStr, "Invalid Access");
}


// Invalid memory access This error occurs then trying to access a block of heap memory that has not yet or has already been deallocated.

// In this example, the heap memory has already been deallocated at the time when strcpy() tries to access it:

// char *pStr=new char[25];
// delete[] pStr;
// strcpy(pStr, "Invalid Access");