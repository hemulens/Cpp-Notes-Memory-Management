#include <stdio.h>
#include <cstring>

int main() {
  char str[5];
  strcpy(str,"BufferOverrun");  // too many symbols passed into char str[5];
  printf("%s \n",str);
}


// https://youtu.be/FfyFNqAFlIY

// Overview of memory management problems
// One of the primary advantages of C++ is the flexibility and control of resources such as memory it gives to the programmer. This advantage is further amplified by a significant increase in the performance of C++ programs compared to other languages such as Python or Java.

// However, these advantages come at a price as they demand a high level of experience from the programer. As Bjarne Stroustrup put it so elegantly:

// "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off".

// In this chapter, we will look at a collection of typical errors in memory management that you need to watch out for.

// Memory Leaks Memory leaks occur when data is allocated on the heap at runtime, but not properly deallocated. A program that forgets to clear a memory block is said to have a memory leak - this may be a serious problem or not, depending on the circumstances and on the nature of the program. For a program that runs, computes something, and quits immediately, memory leaks are usually not a big concern. Memory leaks are mostly problematic for programs that run for a long time and/or use large data structures. In such a case, memory leaks can gradually fill the heap until allocation requests can no longer be properly met and the program stops responding or crashes completely. We will look at an example further down in this section.

// Buffer Overruns Buffer overruns occur when memory outside the allocated limits is overwritten and thus corrupted. One of the resulting problems is that this effect may not become immediately visible. When a problem finally does occur, cause and effect are often hard to discern. It is also sometimes possible to inject malicious code into programs in this way, but this shall not be discussed here.

// In this example, the allocated stack memory is too small to hold the entire string, which results in a segmentation fault:

// char str[5];
// strcpy(str,"BufferOverrun");
// printf("%s",str);
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
// Incorrect pairing of allocation and deallocation Freeing a block of memory more than once will cause a program to crash. This can happen when a block of memory is freed that has never been allocated or has been freed before. Such behavior could also occur when improper pairings of allocation and deallocation are used such as using malloc() with delete or new with free().

// In this first example, the wrong new and delete are paired

// double *pDbl=new double[5];
// delete pDbl;
// In this second example, the pairing is correct but a double deletion is performed:

// char *pChr=new char[5];
// delete[] pChr;
// delete[] pChr;
// Invalid memory access This error occurs then trying to access a block of heap memory that has not yet or has already been deallocated.

// In this example, the heap memory has already been deallocated at the time when strcpy() tries to access it:

// char *pStr=new char[25];
// delete[] pStr;
// strcpy(pStr, "Invalid Access");
// Debugging memory leaks with Valgrind

// https://youtu.be/y0m_6V8fvzA