#include <stdio.h> 
#include <stdlib.h> // for malloc
  
int main() 
{ 
    // void *p = malloc(sizeof(int));   // this won't work
    int *p = (int*)malloc(sizeof(int)); // do not rely on pre-initialization
    printf("address=%p, value=%d\n", p, *p);

    return 0; 
}




// Allocating Dynamic Memory
// To allocate dynamic memory on the heap means to make a contiguous memory area accessible to the program at runtime and to mark this memory as occupied so that no one else can write there by mistake.

// To reserve memory on the heap, one of the two functions malloc (stands for Memory Allocation) or calloc (stands for Cleared Memory Allocation) is used. The header file stdlib.h or malloc.h must be included to use the functions.

// Here is the syntax of malloc and calloc in C/C++:


// pointer_name = (cast-type*) malloc(size);
// pointer_name = (cast-type*) calloc(num_elems, size_elem);

// malloc is used to dynamically allocate a single large block of memory with the specified size. It returns a pointer of type void which can be cast into a pointer of any form.

// calloc is used to dynamically allocate the specified number of blocks of memory of the specified type. It initializes each block with a default value '0'.

// Both functions return a pointer of type void which can be cast into a pointer of any form. If the space for the allocation is insufficient, a NULL pointer is returned.

// In the code example on the right, a block of memory the size of an integer is allocated using malloc.

// The sizeof command is a convenient way of specifying the amount of memory (in bytes) needed to store a certain data type. For an int, sizeof returns 4. However, when compiling this code, the following warning is generated on my machine:


// warning: ISO C++ does not allow indirection on operand of type 'void *' [-Wvoid-ptr-dereference] 

// printf("address=%p, value=%d", p, *p);
// In the virtual workspace, when compiling with g++, an error is thrown instead of a warning.

// The problem with void pointers is that there is no way of knowing the offset to the end of the allocated memory block. For an int, this would be 4 bytes but for a double, the offset would be 8 bytes. So in order to retrieve the entire block of memory that has been reserved, we need to know the data type and the way to achieve this with malloc is by casting the return pointer:

// int *p = (int*)malloc(sizeof(int));

// This code now produces the following output without compiler warnings: address=0x1003001f0, value=0

// Obviously, the memory has been initialized with 0 in this case. However, you should not rely on pre-initialization as this depends on the data type as well as on the compiler you are using.

// At compile time, only the space for the pointer is reserved (on the stack). When the pointer is initialized, a block of memory of sizeof(int) bytes is allocated (on the heap) at program runtime. The pointer on the stack then points to this memory location on the heap.