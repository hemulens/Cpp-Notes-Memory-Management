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
  MyMovableClass obj1(100);   // constructor
  MyMovableClass obj2(200);   // constructor
  MyMovableClass obj3(obj1);  // copy constructor
  MyMovableClass obj4 = obj1; // copy constructor – Interestingly, even though the creation of obj4 looks like an assignment, the compiler calls the copy constructor in this case.
  obj4 = obj2;                // copy assignment operator

  // compile using -std=c++11
  // ( -fno-elide-constructors)

  return 0;
}


// Let us look at some code examples:


// int main()
// {
//     MyMovableClass obj1(100), obj2(200); // constructor

//     MyMovableClass obj3(obj1); // copy constructor

//     MyMovableClass obj4 = obj1; // copy constructor

//     obj4 = obj2; // copy assignment operator

//     return 0;
// }
// If you compile and run this code, be sure to use the -std=c++11 flag. The reasons for this will be explained below.

// In the code above, in total, four instances of MyMovableClass are constructed here. While obj1 and obj2 are created using the conventional constructor, obj3 is created using the copy constructor instead according to our implementation. Interestingly, even though the creation of obj4 looks like an assignment, the compiler calls the copy constructor int this case. Finally, the last line calls the copy assignment operator. The output of the above main function looks like the following:


// CREATING instance of MyMovableClass at 0x7ffeefbff718 allocated with size = 400 bytes

// CREATING instance of MyMovableClass at 0x7ffeefbff708 allocated with size = 800 bytes

// COPYING content of instance 0x7ffeefbff718 to instance 0x7ffeefbff6e8

// COPYING content of instance 0x7ffeefbff718 to instance 0x7ffeefbff6d8

// ASSIGNING content of instance 0x7ffeefbff708 to instance 0x7ffeefbff6d8

// DELETING instance of MyMovableClass at 0x7ffeefbff6d8
// DELETING instance of MyMovableClass at 0x7ffeefbff6e8
// DELETING instance of MyMovableClass at 0x7ffeefbff708
// DELETING instance of MyMovableClass at 0x7ffeefbff718

// *** IMPORTANT

// Note that the compiler has been called with the option -fno-elide-constructors to turn off an optimization techniques called copy elision, which would make it harder to understand the various calls and the operations they entail. This technique is guaranteed to be used as of C++17, which is why we are also reverting to the C++11 standard for the remainder of this chapter using -std=c++11. Until now, no move operation has been performed yet as all of the above calls were involving lvalues.