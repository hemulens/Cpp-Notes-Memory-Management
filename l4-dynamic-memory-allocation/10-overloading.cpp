#include <iostream>
#include <stdlib.h>

class MyClass {
  int _mymember;
  // double _mymember;  // if double instead of int, size_t size in overloaded new will adapt

  public:
    MyClass() {
      std::cout << "Constructor is called\n";
      std::cout << "Address of _mymember: " << &_mymember << std::endl;
    }

    ~MyClass() {
      std::cout << "Destructor is called\n";
    }

    void *operator new(size_t size) {
      std::cout << "new: Allocating " << size << " bytes of memory" << std::endl;
      void *p = malloc(size);

      return p;
    }

    void operator delete(void *p) {
      std::cout << "delete: Memory is freed again " << std::endl;
      free(p);
    }
};

int main() {
  MyClass *p = new MyClass();
  std::cout << "Address of object: " << &p << std::endl;
  delete p;
}


// Overloading new and delete
// One of the major advantages of new/delete over free/malloc is the possibility of overloading. While both malloc and free are function calls and thus can not be changed easily, new and delete are operators and can thus be overloaded to integrate customized functionality, if needed.

// The syntax for overloading the new operator looks as follows:

// void* operator new(size_t size);

// The operator receives a parameter size of type size_t, which specifies the number of bytes of memory to be allocated. The return type of the overloaded new is a void pointer, which references the beginning of the block of allocated memory.

// The syntax for overloading the delete operator looks as follows:

// void operator delete(void*);

// The operator takes a pointer to the object which is to be deleted. As opposed to new, the operator delete does not have a return value.

// Let us consider the example on the right.

// ***
// In the code to the right, both the new and the delete operator are overloaded. In new, the size of the class object in bytes is printed to the console. Also, a block of memory of that size is allocated on the heap and the pointer to this block is returned. In delete, the block of memory is freed again. The console output of this example looks as follows:

// new: Allocating 4 bytes of memory
// Constructor is called
// Destructor is called
// delete: Memory is freed again 
// As can be seen from the order of text output, memory is instantiated in new before the constructor is called, while the order is reversed for the destructor and the call to delete.