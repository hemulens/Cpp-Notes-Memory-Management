#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main() {
  // reserve memory for two integers
  int *p = (int*)malloc(2*sizeof(int));
  p[0] = 1;
  p[1] = 2;

  // resize memory to hold four integers
  p = (int*)realloc(p, 4*sizeof(int));
  p[2] = 3;
  p[3] = 4;

  // resize memory again to hold two integers
  p = (int*)realloc(p, 2*sizeof(int));

  printf("address=%p, value=%d\n", p+0, *(p+0));  // valid
  printf("address=%p, value=%d\n", p+1, *(p+1));  // valid
  printf("address=%p, value=%d\n", p+2, *(p+2));  // invalid (memory can be reclaimed by another function and could lead to returnin undefined)
  printf("address=%p, value=%d\n", p+3, *(p+3));  // invalid

  std::cout << "Test: " << p+1 << std::endl;

  return 0;
}


// The size of the memory area reserved with malloc or calloc can be increased or decreased with the realloc function.

// pointer_name = (cast-type*) realloc( (cast-type*)old_memblock, new_size );

// To do this, the function must be given a pointer to the previous memory area and the new size in bytes. Depending on the compiler, the reserved memory area is either (a) expanded or reduced internally (if there is still enough free heap after the previously reserved memory area) or (b) a new memory area is reserved in the desired size and the old memory area is released afterwards.

// The data from the old memory area is retained, i.e. if the new memory area is larger, the data will be available within new memory area as well. If the new memory area is smaller, the data from the old area will be available only up until the site of the new area - the rest is lost.

// In the example on the right, a block of memory of initially 8 bytes (two integers) is resized to 16 bytes (four integers) using realloc.

// Note that realloc has been used to increase the memory size and then decrease it immediately after assigning the values 3 and 4 to the new blocks. The output looks like the following:


// address=0x100300060, value=1
// address=0x100300064, value=2
// address=0x100300068, value=3
// address=0x10030006c, value=4
// Interestingly, the pointers p+2 and p+3 can still access the memory location they point to. Also, the original data (numbers 3 and 4) is still there. So realloc will not erase memory but merely mark it as "available" for future allocations. It should be noted however that accessing a memory location after such an operation must be avoided as it could cause a segmentation fault. We will encounter segmentation faults soon when we discuss "dangling pointers" in one of the next lessons.