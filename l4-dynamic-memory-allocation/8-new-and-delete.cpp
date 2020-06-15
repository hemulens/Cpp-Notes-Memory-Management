// Comparing malloc with new
// The functions malloc and free are library function and represent the default way of allocating and deallocating memory in C. In C++, they are also part of the standard and can be used to allocate blocks of memory on the heap.

// With the introduction of classes and object oriented programming in C++ however, memory allocation and deallocation has become more complex: When an object is created, its constructor needs to be called to allow for member initialization. Also, on object deletion, the destructor is called to free resources and to allow for programmer-defined clean-up tasks. For this reason, C++ introduces the operators new / delete, which represent the object-oriented counterpart to memory management with malloc / free.



#include <stdlib.h>
#include <iostream>

class MyClass
{
private:
  int *_number;

public:
  MyClass()
  {
      std::cout << "Allocate memory\n";
      _number = (int *)malloc(sizeof(int));
  }
  ~MyClass()
  {
      std::cout << "Delete memory\n";
      free(_number);
  }
  void setNumber(int number)
  {
      *_number = number;
      std::cout << "Number: " << _number << "\n";
  }
};


int main()
{
  // MALLOC / CALLOC will not work
  // allocate memory using malloc
  // comment these lines out to run the example below
  // MyClass *myClass = (MyClass *)malloc(sizeof(MyClass));
  // myClass->setNumber(42); // EXC_BAD_ACCESS
  // free(myClass);
  
// allocate memory using new
  MyClass *myClass = new MyClass();
  myClass->setNumber(42); // works as expected
  delete myClass;

  return 0;
}


// If we were to create a C++ object with malloc, the constructor and destructor of such an object would not be called. Consider the class on the right. The constructor allocates memory for the private element _number (yes, we could have simply used int instead of int*, but that's for educational purposes only), and the destructor releases memory again. The setter method setNumber finally assigns a value to _number under the assumption that memory has been allocated previously.

// In main, we will allocate memory for an instance of MyClass using both malloc/ free and new/delete.

// With malloc, the program crashes on calling the method setNumber, as no memory has been allocated for _number - because the constructor has not been called. Hence, an EXC_BAD_ACCESS error occurs, when trying to access the memory location to which _number is pointing. With _new, the output looks like the following:

// Allocate memory
// Number: 42
// Delete memory

// Before we go into further details of new/delete, let us briefly summarize the major differences between malloc/free and new/delete:

// Constructors / Destructors Unlike malloc( sizeof(MyClass) ), the call new MyClass() calls the constructor. Similarly, delete calls the destructor.

// Type safety malloc returns a void pointer, which needs to be cast into the appropriate data type it points to. This is not type safe, as you can freely vary the pointer type without any warnings or errors from the compiler as in the following small example: MyObject *p = (MyObject*)malloc(sizeof(int));

// In C++, the call MyObject *p = new MyObject() returns the correct type automatically - it is thus type-safe.

// Operator Overloading As malloc and free are functions defined in a library, their behavior can not be changed easily. The new and delete operators however can be overloaded by a class in order to include optional proprietary behavior. We will look at an example of overloading new further down in this section.

// ***
// Creating and Deleting Objects
// As with malloc and free, a call to new always has to be followed by a call to delete to ensure that memory is properly deallocated. If the programmer forgets to call delete on the object (which happens quite often, even with experienced programmers), the object resides in memory until the program terminates at some point in the future causing a memory leak.

// Let us revisit a part of the code example to the right:


// myClass = new MyClass();
// myClass->setNumber(42); // works as expected
// delete myClass;
// The call to new has the following consequences:

// Memory is allocated to hold a new object of type MyClass
// A new object of type MyClass is constructed within the allocated memory by calling the constructor of MyClass
// The call to delete causes the following:

// The object of type MyClass is destroyed by calling its destructor
// The memory which the object was placed in is deallocated