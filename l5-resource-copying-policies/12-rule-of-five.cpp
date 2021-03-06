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
    delete[] _data;  // assumption that an object lived before
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

    delete[] _data;  // assumption that an object lived before

    _data = source._data;  // perhaps mistake (should be like in copy assignemnt operator)
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
  MyMovableClass obj1(10);  // regular constructor
  // MyMovableClass obj2(obj1);  // copy constructor
  // obj2 = obj1; // copy assignment operator
  // MyMovableClass obj2(createObject(10));  // create object function: EXPENSIVE – creating the temporary rvalue and executing the copy constructor (which clones the object)
  MyMovableClass obj3(std::move(obj1));  // move constructor: INEXPENSIVE
  MyMovableClass obj4 = std::move(obj1);  // move assignment operator. No std::cout "MOVING (assign) instance" is visible.

  return 0;
}

// The move constructor
// The basic idea to optimize the code from the last example is to "steal" the rvalue generated by the compiler during the return-by-value operation and move the expensive data in the source object to the target object - not by copying it but by redirecting the data handles. Moving data in such a way is always cheaper than making copies, which is why programmers are highly encouraged to make use of this powerful tool.

// The following diagram illustrates the basic principle of moving a resource from a source object to a destination object: [rule-of-five.png]

// In order to achieve this, we will be using a construct called move constructor, which is similar to the copy constructor with the key difference being the re-use of existing data without unnecessarily copying it. In addition to the move constructor, there is also a move assignment operator, which we need to look at.

// Just like the copy constructor, the move constructor builds an instance of a class using a source instance. The key difference between the two is that with the move constructor, the source instance will no longer be usable afterwards. Let us take a look at an implementation of the move constructor for our MyMovableClass:

//     MyMovableClass(MyMovableClass &&source) // 4 : move constructor
//     {
//         std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
//         _data = source._data;
//         _size = source._size;
//         source._data = nullptr;
//         source._size = 0;
//     }
// If you haven't already added it, you can add this code to the rule_of_five.cpp file to the right.

// In this code, the move constructor takes as its input an rvalue reference to a source object of the same class. In doing so, we are able to use the object within the scope of the move constructor. As can be seen, the implementation copies the data handle from source to target and immediately invalidates source after copying is complete. Now, this is responsible for the data and must also release memory on destruction - the ownership has been successfully changed (or moved) without the need to copy the data on the heap.

// When are move semantics used?
// Now that we have seen how move semantics work, let us take a look at situations where they actually apply.

// One of the primary areas of application are cases, where heavy-weight objects need to be passed around in a program. Copying these without move semantics can cause series performance issues. The idea in this scenario is to create the object a single time and then "simply" move it around using rvalue references and move semantics.

// A second area of application are cases where ownership needs to be transferred (such as with unique pointers, as we will soon see). The primary difference to shared references is that with move semantics we are not sharing anything but instead we are ensuring through a smart policy that only a single object at a time has access to and thus owns the resource.


// IMPORTANT: 
// Advantages of rvalue refences (and std::move) over between copying with exclusive owbership policy: 
// Passing values like this improves performance as no temporary copy needs to be made anymore and ownership changes, since the object the reference binds to has been abandoned by the caller and now binds to a handle which is available only to the receiver. This could not have been achieved with lvalue references as any change to the object that binds to the lvalue reference would also be visible on the caller side.




// The Rule of Five
// By adding both the move constructor and the move assignment operator to our MyMovableClass, we have adhered to the Rule of Five. This rule is an extension of the Rule of Three which we have already seen and exists since the introduction of the C++11 standard. The Rule of Five is especially important in resource management, where unnecessary copying needs to be avoided due to limited resources and performance reasons. Also, all the STL container classes such as std::vector implement the Rule of Five and use move semantics for increased efficiency.

// The Rule of Five states that if you have to write one of the functions listed below then you should consider implementing all of them with a proper resource management policy in place. If you forget to implement one or more, the compiler will usually generate the missing ones (without a warning) but the default versions might not be suitable for the purpose you have in mind. The five functions are:

// 1) The destructor: Responsible for freeing the resource once the object it belongs to goes out of scope.

// 2) The assignment operator: The default assignment operation performs a member-wise shallow copy, which does not copy the content behind the resource handle. If a deep copy is needed, it has be implemented by the programmer.

// 3) The copy constructor: As with the assignment operator, the default copy constructor performs a shallow copy of the data members. If something else is needed, the programmer has to implement it accordingly.

// 4) The move constructor: Because copying objects can be an expensive operation which involves creating, copying and destroying temporary objects, rvalue references are used to bind to an rvalue. Using this mechanism, the move constructor transfers the ownership of a resource from a (temporary) rvalue object to a permanent lvalue object.

// 5) The move assignment operator: With this operator, ownership of a resource can be transferred from one object to another. The internal behavior is very similar to the move constructor.