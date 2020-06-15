#include <iostream>
#include <stdlib.h>

class MyClass {
  int _mymember;

  public:
    MyClass() {
      std::cout << "Constructor is called\n";
    }

    ~MyClass() {
      std::cout << "Destructor is called\n";
    }

    void *operator new[](size_t size) {
      std::cout << "new: Allocating " << size << " bytes of memory" << std::endl;
      void *p = malloc(size);

      return p;
    }

    void operator delete[](void *p) {
      std::cout << "delete: Memory is freed again " << std::endl;
      free(p);
    }
};

int main() {
  MyClass *p = new MyClass[3]();
  std::cout << "p[0]: " << &p[0] << std::endl;
  delete[] p;
}


// Overloading new[] and delete[]¶
// In addition to the new and delete operators we have seen so far, we can use the following code to create an array of objects:


// void* operator new[](size_t size);
// void operator delete[](void*);
// Let us consider the example on the right, which has been slightly modified to allocate an array of objects instead of a single one.


// In main, we are now creating an array of three objects of MyClass. Also, the overloaded new and delete operators have been changed to accept arrays. Let us take a look at the console output:


// new: Allocating 20 bytes of memory
// Constructor is called
// Constructor is called
// Constructor is called
// Destructor is called
// Destructor is called
// Destructor is called
// delete: Memory is freed again 
// Interestingly, the memory requirement is larger than expected: With new, the block size was 4 bytes, which is exactly the space required for a single integer. Thus, with three integers, it should now be 12 bytes instead of 20 bytes. The reason for this is the memory allocation overhead that the compiler needs to keep track of the allocated blocks of memory - which in itself consumes memory. If we change the above call to e.g. new MyClass[100](), we will see that the overhead of 8 bytes does not change:


// new: Allocating 408 bytes of memory
// Constructor is called
// …
// Destructor is called
// delete: Memory is freed again 

// ***

// Reasons for overloading new and delete
// Now that we have seen how to overload the new and delete operators, let us summarize the major scenarios where it makes sense to do this:

// The overloaded new operator function allows to add additional parameters. Therefore, a class can have multiple overloaded new operator functions. This gives the programmer more flexibility in customizing the memory allocation for objects.

// Overloaded the new and delete operators provides an easy way to integrate a mechanism similar to garbage collection capabilities (such as in Java), as we will shorty see later in this course.

// By adding exception handling capabilities into new and delete, the code can be made more robust.

// It is very easy to add customized behavior, such as overwriting deallocated memory with zeros in order to increase the security of critical application data.


// "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off".