#include <stdlib.h>
#include <iostream>

class MyMovableClass
{
private:
  int _size;
  int *_data;

public:
  MyMovableClass(size_t size) // constructor
  {
    _size = size;
    _data = new int[_size];
    std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size * sizeof(int) << " bytes" << std::endl;
  }

  ~MyMovableClass() // 1 : destructor
  {
    std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
    delete[] _data;
  }

  MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
  {
    _size = source._size;
    _data = new int[_size];
    *_data = *source._data;
    std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
  }

  MyMovableClass &operator=(const MyMovableClass &source) // 3 : copy assignment operator
  {
    std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
      return *this;
    delete[] _data;
    _data = new int[source._size];
    *_data = *source._data;
    _size = source._size;
    return *this;
  }
  MyMovableClass(MyMovableClass &&source) // 4 : move constructor
  {
    std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
    _data = source._data;
    _size = source._size;
    source._data = nullptr;
    source._size = 0;
  }
  MyMovableClass &operator=(MyMovableClass &&source) // 5 : move assignment operator
  {
    std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
      return *this;

    delete[] _data;

    _data = source._data;
    _size = source._size;

    source._data = nullptr;
    source._size = 0;

    return *this;
  }
};

// Sergei's experiment from the file 11: EXPENSIVE – the data is dynamically allocated on the stack, which is then copied from the temporary object to its target destination. This means that two expensive memory operations are performed with the first occurring during the creation of the temporary rvalue and the second during the execution of the copy constructor.
MyMovableClass createObject(int size)
{
  MyMovableClass obj(size); // regular constructor
  return obj;               // return MyMovableClass object by value
}

// Lecture example
void useObject(MyMovableClass obj)
{
  std::cout << "using object " << &obj << std::endl;
}

int main()
{
  MyMovableClass obj1(100); // constructor

  useObject(obj1);  // EXPENSIVE!

  useObject(200);
  // or useObject(std::move(obj1));

  return 0;
}

// Let us now consider a final example:

// void useObject(MyMovableClass obj)
// {
//     std::cout << "using object " << &obj << std::endl;
// }

// int main()
// {
//     MyMovableClass obj1(100); // constructor

//     useObject(obj1);

//     return 0;
// }
// In this case, an instance of MyMovableClass, obj1, is passed to a function useObject by value, thus making a copy of it.

// Let us take an immediate look at the output of the program, before going into details:

// (1)
// CREATING instance of MyMovableClass at 0x7ffeefbff718 allocated with size = 400 bytes

// (2)
// COPYING content of instance 0x7ffeefbff718 to instance 0x7ffeefbff708

// using object 0x7ffeefbff708

// (3)
// DELETING instance of MyMovableClass at 0x7ffeefbff708

// (4)
// CREATING instance of MyMovableClass at 0x7ffeefbff6d8 allocated with size = 800 bytes

// (5)
// MOVING (c'tor) instance 0x7ffeefbff6d8 to instance 0x7ffeefbff6e8

// using object 0x7ffeefbff6e8

// DELETING instance of MyMovableClass at 0x7ffeefbff6e8
// DELETING instance of MyMovableClass at 0x7ffeefbff6d8
// DELETING instance of MyMovableClass at 0x7ffeefbff718

// First, we are creating an instance of MyMovableClass, obj1, by calling the constructor of the class (1).

// Then, we are passing obj1 by-value to a function useObject, which causes a temporary object obj to be instantiated, which is a copy of obj1 (2) and is deleted immediately after the function scope is left (3).

// Then, the function is called with a temporary instance of MyMovableClass as its argument, which creates a temporary instance of MyMovableClass as an rvalue (4). But instead of making a copy of it as before, the move constructor is used (5) to transfer ownership of that temporary object to the function scope, which saves us one expensive deep-copy.