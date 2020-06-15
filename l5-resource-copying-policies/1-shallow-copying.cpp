#include <iostream>

class MyClass
{
private:
    int *_myInt;

public:
    MyClass()
    {
        _myInt = (int *)malloc(sizeof(int));
    };
    ~MyClass()
    {
        free(_myInt);
    };
    void printOwnAddress() { std::cout << "Own address on the stack is " << this << std::endl; }
    void printMemberAddress() { std::cout << "Managing memory block on the heap at " << _myInt << std::endl; }
};

int main()
{
    // instantiate object 1
    MyClass myClass1;
    myClass1.printOwnAddress();
    myClass1.printMemberAddress();

    // copy object 1 into object 2
    MyClass myClass2(myClass1); // copy constructor
    myClass2.printOwnAddress();
    myClass2.printMemberAddress();

    return 0;
}


// Consider the example on the right of managing access to a block of heap memory.

// The class MyClass has a private member, which is a pointer to a heap-allocated integer. Allocation is performed in the constructor, deallocation is done in the destructor. This means that the memory block of size sizeof(int) is allocated when the objects myClass1 and myClass2 are created on the stack and deallocated when their scope is left, which happens at the end of the main. The difference between myClass1 and myClass2 is that the latter is instantiated using the copy constructor, which duplicates the members in myClass1 - including the pointer to the heap memory where _myInt resides.

// The output of the program looks like the following:


// Own address on the stack is 0x7ffeefbff670
// Managing memory block on the heap at 0x100300060
// Own address on the stack is 0x7ffeefbff658
// Managing memory block on the heap at 0x100300060
// copy_constructor_1(87582,0x1000a95c0) malloc: *** error for object 0x100300060: pointer being freed was not allocated
// Note that in the workspace, the error will read: *** Error in './a.out': double free or corruption (fasttop): 0x0000000001133c20 ***

// From the output we can see that the stack address is different for myClass1 and myClass2 - as was expected. The address of the managed memory block on the heap however is identical. This means that when the first object goes out of scope, it releases the memory resource by calling free in its destructor. The second object does the same - which causes the program to crash as the pointer is now referencing an invalid area of memory, which has already been freed.

// The default behavior of both copy constructor and assignment operator is to perform a shallow copy as with the example above. The following figure illustrates the concept: [shallow-copy-1.png]

// Fortunately, in C++, the copying process can be controlled by defining a tailored copy constructor as well as a copy assignment operator. The copying process must be closely linked to the respective resource release mechanism and is often referred to as copy-ownership policy. Tailoring the copy constructor according to your memory management policy is an important choice you often need to make when designing a class. In the following, we will closely examine several well-known copy-ownership policies.

