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

  // useObject(obj1);  // EXPENSIVE

  // useObject(200);  
  useObject(std::move(obj1));  // after this, obj1 isn't accessible within main anymore!

  return 0;
}


// Moving lvalues
// There is one final aspect we need to look at: In some cases, it can make sense to treat lvalues like rvalues. At some point in your code, you might want to transfer ownership of a resource to another part of your program as it is not needed anymore in the current scope. But instead of copying it, you want to just move it as we have seen before. The "problem" with our implementation of MyMovableClass is that the call useObject(obj1) will trigger the copy constructor as we have seen in one of the last examples. But in order to move it, we would have to pretend to the compiler that obj1 was an rvalue instead of an lvalue so that we can make an efficient move operation instead of an expensive copy.

// There is a solution to this problem in C++, which is std::move. This function accepts an lvalue argument and returns it as an rvalue without triggering copy construction. So by passing an object to std::move we can force the compiler to use move semantics, either in the form of move constructor or the move assignment operator:


// int main()
// {
//     MyMovableClass obj1(100); // constructor

//     useObject(std::move(obj1));

//     return 0;
// }
// Nothing much has changed, apart from obj1 being passed to the std::move function. The output would look like the following:


// CREATING instance of MyMovableClass at 0x7ffeefbff718 allocated with size = 400 bytes

// MOVING (c'tor) instance 0x7ffeefbff718 to instance 0x7ffeefbff708

// using object 0x7ffeefbff708

// DELETING instance of MyMovableClass at 0x7ffeefbff708
// DELETING instance of MyMovableClass at 0x7ffeefbff718
// By using std::move, we were able to pass the ownership of the resources within obj1 to the function useObject. The local copy obj1 in the argument list was created with the move constructor and thus accepted the ownership transfer from obj1 to obj . Note that after the call to useObject, the instance obj1 has been invalidated by setting its internal handle to null and thus may not be used anymore within the scope of main (even though you could theoretically try to access it, but this would be a really bad idea).

// [https://youtu.be/QR279x7G9pA]