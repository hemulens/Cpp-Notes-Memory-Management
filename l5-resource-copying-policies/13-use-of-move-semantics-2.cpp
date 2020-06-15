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

int main()
{
  MyMovableClass obj1(100); // constructor

  obj1 = MyMovableClass(200); // move assignment operator

  MyMovableClass obj2 = MyMovableClass(300); // move constructor

  return 0;
}


// Now consider the following main function instead:


// int main()
// {
//     MyMovableClass obj1(100); // constructor

//     obj1 = MyMovableClass(200); // move assignment operator

//     MyMovableClass obj2 = MyMovableClass(300); // move constructor 

//     return 0;
// }
// In this version, we also have an instance of MyMovableClass, obj1. Then, a second instance of MyMovableClass is created as an rvalue, which is assigned to obj1. Finally, we have a second lvalue obj2, which is created by assigning it an rvalue object. Let us take a look at the output of the program:


// CREATING instance of MyMovableClass at 0x7ffeefbff718 allocated with size = 400 bytes

// CREATING instance of MyMovableClass at 0x7ffeefbff708 allocated with size = 800 bytes

// MOVING (assign) instance 0x7ffeefbff708 to instance 0x7ffeefbff718

// DELETING instance of MyMovableClass at 0x7ffeefbff708

// CREATING instance of MyMovableClass at 0x7ffeefbff6d8 allocated with size = 1200 bytes

// MOVING (c'tor) instance 0x7ffeefbff6d8 to instance 0x7ffeefbff6e8

// DELETING instance of MyMovableClass at 0x7ffeefbff6d8
// DELETING instance of MyMovableClass at 0x7ffeefbff6e8
// DELETING instance of MyMovableClass at 0x7ffeefbff718

// By looking at the stack addresses of the objects, we can see that the temporary object at 0x7ffeefbff708 is moved to 0x7ffeefbff718 using the move assignment operator we wrote earlier, because the instance obj1 is assigned an rvalue. As expected from an rvalue, its destructor is called immediately afterwards. But as we have made sure to null its data pointer in the move constructor, the actual data will not be deleted. The advantage from a performance perspective in this case is that no deep-copy of the rvalue object needs to be made, we are simply redirecting the internal resource handle thus making an efficient shallow copy.

// Next, another temporary instance with a size of 1200 bytes is created as a temporary object and "assigned" to obj3. Note that while the call looks like an assignment, the move constructor is called under the hood, making the call identical to MyMovableClass obj2(MyMovableClass(300));. By creating obj3 in such a way, we are reusing the temporary rvalue and transferring ownership of its resources to the newly created obj3.