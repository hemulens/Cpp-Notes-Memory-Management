#include <stdio.h>

int main() {
  double *pDbl = new double[5];
  printf("pDbl: address = %p, value = %f \n", pDbl, *pDbl+0);   // weird behavior
  // delete pDbl;  // incorrect
  delete[] pDbl;  // correct

  char *pChr = new char[5];
  printf("pChr: address = %p, value = %c \n", pChr, *pChr+0);
  delete[] pChr;
  // delete[] pChr;  // Don't delete things twice
}


// Incorrect pairing of allocation and deallocation Freeing a block of memory more than once will cause a program to crash. This can happen when a block of memory is freed that has never been allocated or has been freed before. Such behavior could also occur when improper pairings of allocation and deallocation are used such as using malloc() with delete or new with free().

// In this first example, the wrong new and delete are paired

// double *pDbl=new double[5];
// delete pDbl;
// In this second example, the pairing is correct but a double deletion is performed:

// char *pChr=new char[5];
// delete[] pChr;
// delete[] pChr;