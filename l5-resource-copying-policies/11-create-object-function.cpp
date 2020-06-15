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

// One more way to instantiate MyMovableClass object by using createObject() function.
MyMovableClass createObject(int size) {
  MyMovableClass obj(size);  // regular constructor
  return obj;  // return MyMovableClass object by value
}

int main() {
  MyMovableClass obj1(10);  // regular constructor
  // MyMovableClass obj2(obj1);  // copy constructor
  // obj2 = obj1;  // copy assignment operator (doesn't call the copy constructor, because the object already exists)
  MyMovableClass obj3 = obj1;  // copy assignment operator (calls the copy constructor, because obj3 is being instantiated)
  // *** Here, we are instantiating obj3 in the same statement; hence the copy assignment operator would not be called.

  MyMovableClass obj4 = createObject(10);  // createObject(10) returns a temporary copy of the object as an rvalue, which is passed to the copy constructor. It would not print the cout statement of copy constructor on the console. This is because the copy constructor is called on the temporary object. EXPENSIVE => read below

  // obj4 = createObject(10); // call to copy assignment operator. The similar two expensive memory operations would be performed with the assignment operator if we execute this statement. EXPENSIVE: In this call to copy assignment operator, it would first erase the memory of obj4, then reallocate it during the creation of the temporary object; and then copy the data from the temporary object to obj4. From a performance viewpoint, this code involves far too many copies, making it inefficient - especially with large data structures. Prior to C++11, the proper solution in such a case was to simply avoid returning large data structures by value to prevent the expensive and unnecessary copying process. With C++11 however, there is a way we can optimize this and return even large data structures by value. The solution is the move constructor and the Rule of Five.

  /*
   * You can try executing the statement below as well
   * MyMovableClass obj4(createObject(10));
   */

  MyMovableClass obj5(createObject(10));
}


// The if-statement at the top of the above implementation protects against self-assignment and is standard boilerplate code for the user-defined assignment operator. The remainder of the code is more or less identical to the copy constructor, apart from returning a reference to the own instance using this.

// You might have noticed that both copy constructor and assignment operator take a const reference to the source object as an argument, by which they promise that they won’ (and can’t) modify the content of source.



// ***
// Limitations of Our Current Class Design
// Let us now consider one more way to instantiate MyMovableClass object by using createObject() function. Add the following function definition to the rule_of_three.cpp, outside the scope of the class MyMovableClass:


// MyMovableClass createObject(int size){
//   MyMovableClass obj(size); // regular constructor
//   return obj; // return MyMovableClass object by value
// }
// Note that when a function returns an object by value, the compiler creates a temporary object as an rvalue. Let's call this function inside main to create an obj4 instance, as follows:


// int main(){
//   // call to copy constructor, (alternate syntax)
//   MyMovableClass obj3 = obj1;
//   // Here, we are instantiating obj3 in the same statement; hence the copy assignment operator would not be called.

//   MyMovableClass obj4 = createObject(10);
//   // createObject(10) returns a temporary copy of the object as an rvalue, which is passed to the copy constructor.


//   /*
//    * You can try executing the statement below as well
//    * MyMovableClass obj4(createObject(10));
//    */

//   return 0;
// }
// In the main above, the returned value of createObject(10) is passed to the copy constructor. The function createObject() returns an instance of MyMovableClass by value. In such a case, the compiler creates a temporary copy of the object as an rvalue, which is passed to the copy constructor.

// A special call to copy constructor
// Try compiling and then running the rule_of_three.cpp to notice that MyMovableClass obj4 = createObject(10); would not print the cout statement of copy constructor on the console. This is because the copy constructor is called on the temporary object.

// In our current class design, while creating obj4, the data is dynamically allocated on the stack, which is then copied from the temporary object to its target destination. This means that two expensive memory operations are performed with the first occurring during the creation of the temporary rvalue and the second during the execution of the copy constructor. The similar two expensive memory operations would be performed with the assignment operator if we execute the following statement inside main:


// MyMovableClass obj4 = createObject(10); // Don't write this statement if you have already written it before
// obj4 = createObject(10); // call to copy assignment operator
// In the above call to copy assignment operator, it would first erase the memory of obj4, then reallocate it during the creation of the temporary object; and then copy the data from the temporary object to obj4.

// From a performance viewpoint, this code involves far too many copies, making it inefficient - especially with large data structures. Prior to C++11, the proper solution in such a case was to simply avoid returning large data structures by value to prevent the expensive and unnecessary copying process. With C++11 however, there is a way we can optimize this and return even large data structures by value. The solution is the move constructor and the Rule of Five.