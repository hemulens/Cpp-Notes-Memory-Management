#include <stdio.h>

void CallByValue(int i) {
  int j = 1;
  printf ("call by value: %p\n",&j);
};

void CallByPointer(int *i) {
  int j = 1;
  printf ("call by pointer: %p\n",&j);
};

void CallByReference(int &i) {
  int j = 1;
  printf ("call by reference: %p\n",&j);
};


int main() {
  int i = 0;
  printf ("stack bottom: %p\n",&i);
  CallByValue(i);
  CallByPointer(&i);
  CallByReference(i);

  printf("size of int: %lu\n", sizeof(int));
  printf("size of *int: %lu\n", sizeof(int *));
  return 0;
  // you can use the -m32 compiler flag to build a 32 bit version of the program
}


// Now, we will compare the three strategies we have seen so far with regard to stack memory usage. Consider the code on the right.

// After creating a local variable i in main to give us the address of the stack bottom, we are passing i by-value to our first function. Inside CallByValue, the memory address of a local variable j is printed to the console, which serves as a marker for the stack pointer. With the second function call in main, we are passing a reference to i to CallByPointer. Lastly, the function CallByReference is called in main, which again takes the integer i as an argument. However, from looking at main alone, we can not tell wether i will be passed by value or by reference.

// On my machine, when compiled with g++ (Apple clang version 11.0.0), the program produces the following output:


// stack bottom: 0x7ffeefbff698
// call-by-value: 0x7ffeefbff678
// call-by-pointer: 0x7ffeefbff674
// call-by-reference: 0x7ffeefbff674
// Depending on your system, the compiler you use and the compiler optimization techniques, you man not always see this result. In some cases

// Let us take a look at the respective differences to the stack bottom in turn:

// CallByValue requires 32 bytes of memory. As discussed before, this is reserved for e.g. the function return address and for the local variables within the function (including the copy of i).

// CallByPointer on the other hand requires - perhaps surprisingly - 36 bytes of memory. Let us complete the examination before going into more details on this result.

// CallByReference finally has the same memory requirements as CallByPointer.


// Quiz: Why does CallByValue require more memory?
// In this section, we have argued at length that passing a parameter by reference avoids a costly copy and should - in many situations - be preferred over passing a parameter by value. Yet, in the experiment above, we have witnessed the exact opposite.

// Can you explain why?

// Let us take a look at the size of the various parameter types using the sizeof command:


// printf("size of int: %lu\n", sizeof(int));
// printf("size of *int: %lu\n", sizeof(int *));
// The output here is


// size of int: 4
// size of *int: 8
// Obviously, the size of the pointer variable is larger than the actual data type. As my machine has a 64 bit architecture, an address requires 8 byte.

// As an experiment, you could use the -m32 compiler flag to build a 32 bit version of the program. This yields the following output:


// size of int: 4
// size of *int: 4
// In order to benefit from call-by-reference, the size of the data type passed to the function has to surpass the size of the pointer on the respective architecture (i.e. 32 bit or 64 bit).