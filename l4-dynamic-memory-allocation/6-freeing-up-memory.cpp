#include <stdio.h>
#include <stdlib.h>

int main() {
  int *p = (int*)malloc(100); 
  *p = 25;
  free(p);

  printf("address: %p, value: %d\n", p, *p);  // here, the memory is freed up, but the value is kept unless the memory is allocated for another variable
  return 0;
}


// Freeing up Memory
// If memory has been reserved, it should also be released as soon as it is no longer needed. If memory is reserved regularly without releasing it again, the memory capacity may be exhausted at some point. If the RAM memory is completely used up, the data is swapped out to the hard disk, which slows down the computer significantly.

// The free function releases the reserved memory area so that it can be used again or made available to other programs. To do this, the pointer pointing to the memory area to be freed is specified as a parameter for the function. In the free_example.cpp, a memory area is reserved and immediately released again.

// Some things should be considered with dynamic memory management, whose neglect in some cases might result in unpredictable program behavior or a system crash - in some cases unfortunately without error messages from the compiler or the operating system:

// free can only free memory that was reserved with malloc or calloc.

// free can only release memory that has not been released before. Releasing the same block of memory twice will result in an error.

// In the example on the right, a pointer p is copied into a new variable p2, which is then passed to free AFTER the original pointer has been already released.

// free(41143,0x1000a55c0) malloc: *** error for object 0x1003001f0: pointer being freed was not allocated.

// In the workspace, you will see this error:

// *** Error in './a.out': double free or corruption (fasttop): 0x0000000000755010 ***

// The pointer p2 in the example is invalid as soon as free(p) is called. It still holds the address to the memory location which has been freed, but may not access it anymore. Such a pointer is called a "dangling pointer".



// *** IMPORTANT

// Memory allocated with malloc or calloc is not subject to the familiar rules of variables in their respective scopes. This means that they exist independently of block limits until they are released again or the program is terminated. However, the pointers which refer to such heap-allocated memory are created on the stack and thus only exist within a limited scope. As soon as the scope is left, the pointer variable will be lost - but not the heap memory it refers to.