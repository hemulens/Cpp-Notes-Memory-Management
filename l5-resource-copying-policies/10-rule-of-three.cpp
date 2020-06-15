#include <stdlib.h>
#include <iostream>

class MyMovableClass {
  private: 
    int _size;
    int *_data;

  public:
    // constructor
    MyMovableClass(size_t size) {
      _size = size;
      _data = new int[_size];
      std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size * sizeof(int) << " bytes " << std::endl;
    }
    // 1. destructor
    ~MyMovableClass() {
      std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
      delete[] _data;
    }
    // 2. copy constructor
    MyMovableClass(const MyMovableClass &source) {
      _size = source._size;
      _data = new int(_size);
      *_data = *source._data;  // deep copy – creates different pointers
      std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }
    // 3. copy assignment operator
    MyMovableClass &operator=(const MyMovableClass &source) {
      std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
      if (this == &source) {  // protection against self-assignment (i.e. obj1 = obj1)
        return *this;
      }
      delete[] _data;  // in the copy assignment operator, the assumption is that the object lived before – therefore, we need to delete _data memory ptr
      _data = new int[source._size];
      *_data = *source._data;
      _size = source._size;
      return *this;
    }
};

int main() {
  MyMovableClass obj1(10);  // regular constructor
  MyMovableClass obj2(obj1);  // copy constructor
  obj2 = obj1;  // copy assignment operator (doesn't call the copy constructor, because the object already exists)
  // MyMovableClass obj3 = obj1;  // copy assignment operator (calls the copy constructor, because obj3 is being instantiated)
}


// The if-statement at the top of the above implementation protects against self-assignment and is standard boilerplate code for the user-defined assignment operator. The remainder of the code is more or less identical to the copy constructor, apart from returning a reference to the own instance using this.

// You might have noticed that both copy constructor and assignment operator take a const reference to the source object as an argument, by which they promise that they won’ (and can’t) modify the content of source.

