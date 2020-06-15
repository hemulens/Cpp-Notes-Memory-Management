#include <memory>
#include <iostream>

void RawPointer()
{
  int *raw = new int; // create a raw pointer on the heap
  std::cout << "resource " << *raw << " at memory address " << raw << " allocated" << std::endl;
  *raw = 1; // assign a value
  delete raw; // delete the resource again
  std::cout << "resource " << *raw << " at memory address " << raw << " deallocated" << std::endl;
}

void UniquePointer()
{
  std::unique_ptr<int> unique(new int); // create a unique pointer on the stack. A smart pointer is a class template that is declared on the stack and then initialized by a raw pointer (returned by new ) to a heap-allocated object.
  std::cout << "resource " << *unique << " at memory address " << unique << " allocated" << std::endl;
  *unique = 2; // assign a value
  // delete is not neccessary
  std::cout << "resource " << *unique << " at memory address " << unique << " deallocated" << std::endl;
}

int main() 
{
  RawPointer();
  UniquePointer();
}



// The Unique pointer
// A unique pointer is the exclusive owner of the memory resource it represents. There must not be a second unique pointer to the same memory resource, otherwise there will be a compiler error. As soon as the unique pointer goes out of scope, the memory resource is deallocated again. Unique pointers are useful when working with a temporary heap resource that is no longer needed once it goes out of scope.

// The following diagram illustrates the basic idea of a unique pointer: [unique-pointer.png]

// In the example, a resource in memory is referenced by a unique pointer instance sourcePtr. Then, the resource is reassigned to another unique pointer instance destPtr using std::move. The resource is now owned by destPtr while sourcePtr can still be used but does not manage a resource anymore.

// A unique pointer is constructed using the following syntax:

// std::unique_ptr<Type> p(new Type);

// In the example on the right we will see how a unique pointer is constructed and how it compares to a raw pointer.

// The function RawPointer contains the familiar steps of (1) allocating memory on the heap with new and storing the address in a pointer variable, (2) assigning a value to the memory block using the dereferencing operator * and (3) finally deleting the resource on the heap. As we already know, forgetting to call delete will result in a memory leak.

// The function UniquePointer shows how to achieve the same goal using a smart pointer from the standard library. As can be seen, a smart pointer is a class template that is declared on the stack and then initialized by a raw pointer (returned by new ) to a heap-allocated object. The smart pointer is now responsible for deleting the memory that the raw pointer specifies - which happens as soon as the smart pointer goes out of scope. Note that smart pointers always need to be declared on the stack, otherwise the scoping mechanism would not work.

// The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown.

// In the example on the right we will see how a unique pointer is constructed and how it compares to a raw pointer.

// The function RawPointer contains the familiar steps of (1) allocating memory on the heap with new and storing the address in a pointer variable, (2) assigning a value to the memory block using the dereferencing operator * and (3) finally deleting the resource on the heap. As we already know, forgetting to call delete will result in a memory leak.

// The function UniquePointer shows how to achieve the same goal using a smart pointer from the standard library. As can be seen, a smart pointer is a class template that is declared on the stack and then initialized by a raw pointer (returned by new ) to a heap-allocated object. The smart pointer is now responsible for deleting the memory that the raw pointer specifies - which happens as soon as the smart pointer goes out of scope. Note that smart pointers always need to be declared on the stack, otherwise the scoping mechanism would not work.

// The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown.