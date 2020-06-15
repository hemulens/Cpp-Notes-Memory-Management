#include <stdio.h>

void MyFunc() {
    int k = 3; 
    printf ("3: %p \n",&k);
}

int main() {
    int i = 1; 
    printf ("1: %p \n",&i);

    int j = 2; 
    printf ("2: %p \n",&j);

    MyFunc();

    int l = 4; 
    printf ("4: %p \n",&l);

    return 0; 
}

// Stack Growth and Contraction
// In the first experiment, we will look at the behavior of the stack when local variables are allocated and a function is called. Consider the piece of code on the right.

// Within the main function, we see two declarations of local variables i and j followed by a call to MyFunc, where another local variable is allocated. After MyFunc returns, another local variable is allocated in main. The program generates the following output:


// 1: 0x7ffeefbff688 
// 2: 0x7ffeefbff684 
// 3: 0x7ffeefbff65c 
// 4: 0x7ffeefbff680 
// Between 1 and 2, the stack address is reduced by 4 bytes, which corresponds to the allocation of memory for the int j.

// Between 2 and 3, the address pointer is moved by 0x28. We can easily see that calling a function causes a significant amount of memory to be allocated. In addition to the local variable of MyFunc, the compiler needs to store additional data such as the return address.

// Between 3 and 4, MyFunc has returned and a third local variable k has been allocated on the stack. The stack pointer now has moved back to a location which is 4 bytes relative to position 2. This means that after returning from MyFunc, the stack has contracted to the size it had before the function call.

// The following diagram illustrates how the stack grows and contracts during program execution: [3-stack-automatic-memory-allocation-1.png]

// Total Stack Size
// When a thread is created, stack memory is allocated by the operating system as a contiguous block. With each new function call or local variable allocation, the stack pointer is moved until eventually it will reach the bottom of said memory block. Once it exceeds this limit (which is called "stack overflow"), the program will crash. We will try to find out the limit of your computer’s stack memory in the following exercise.

