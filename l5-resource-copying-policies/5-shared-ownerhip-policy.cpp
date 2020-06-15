#include <iostream>

class SharedCopy
{
  private:
    int *_myInt;
    static int _cnt;  // counter

  public:
    SharedCopy(int val);
    ~SharedCopy();
    SharedCopy(SharedCopy &source);
    // MUST have an assignment operator overloading as well – Rule of Three
    SharedCopy &operator=(SharedCopy &source)
    {
      _myInt = source._myInt;
      ++_cnt;
      std::cout << _cnt << "instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
      return *this;
    }
};

int SharedCopy::_cnt = 0;

SharedCopy::SharedCopy(int val)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = val;
    ++_cnt;
    std::cout << "resource allocated at address " << _myInt << std::endl;
}

SharedCopy::~SharedCopy()
{
    --_cnt;
    if (_cnt == 0)
    {
        free(_myInt);
        std::cout << "resource freed at address " << _myInt << std::endl;
    }
    else
    {
        std::cout << "instance at address " << this << " goes out of scope with _cnt = " << _cnt << std::endl;
    }
}

SharedCopy::SharedCopy(SharedCopy &source)
{
    _myInt = source._myInt;
    ++_cnt;
    std::cout << _cnt << " instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
}

int main()
{
    SharedCopy source(42);
    SharedCopy destination1(source);
    SharedCopy destination2(source);
    SharedCopy destination3(source);
    SharedCopy destination4 = source;

    return 0;
}


// Shared ownership policy
// The last ownership policy we will be discussing in this course implements a shared ownership behavior. The idea is to perform a copy or assignment similar to the default behavior, i.e. copying the handle instead of the content (as with a shallow copy) while at the same time keeping track of the number of instances that also point to the same resource. Each time an instance goes out of scope, the counter is decremented. Once the last object is about to be deleted, it can safely deallocate the memory resource. We will see later in this course that this is the central idea of unique_ptr, which is a representative of the group of smart pointers.

// The example on the right illustrates the principle.

// Note that class MyClass now has a static member _cnt, which is incremented every time a new instance of MyClass is created and decrement once an instance is deleted. On deletion of the last instance, i.e. when _cnt==0, the block of memory to which the handle points is deallocated.

// The output of the program is the following:

// resource allocated at address 0x100300060
// 2 instances with handles to address 0x100300060 with _myInt = 42
// 3 instances with handles to address 0x100300060 with _myInt = 42
// 4 instances with handles to address 0x100300060 with _myInt = 42
// instance at address 0x7ffeefbff6f8 goes out of scope with _cnt = 3
// instance at address 0x7ffeefbff700 goes out of scope with _cnt = 2
// instance at address 0x7ffeefbff718 goes out of scope with _cnt = 1
// resource freed at address 0x100300060
// As can be seen, the memory is released only once as soon as the reference counter reaches zero.



// The Rule of Three
// In the previous examples we have taken a first look at several copying policies:

// Default copying
// No copying
// Exclusive ownership
// Deep copying
// Shared ownership
// In the first example we have seen that the default implementation of the copy constructor does not consider the "special" needs of a class which allocates and deallocates a shared resource on the heap. The problem with implicitly using the default copy constructor or assignment operator is that programmers are not forced to consider the implications for the memory management policy of their program. In the case of the first example, this leads to a segmentation fault and thus a program crash.

// In order to properly manage memory allocation, deallocation and copying behavior, we have seen that there is an intricate relationship between destructor, copy constructor and copy assignment operator. To this end, the Rule of Three states that if a class needs to have an overloaded copy constructor, copy assignment operator, ~or~ destructor, then it must also implement the other two as well to ensure that memory is managed consistently. As we have seen, the copy constructor and copy assignment operator (which are often almost identical) control how the resource gets copied between objects while the destructor manages the resource deletion.

// You may have noted that in the previous code example, the class SharedCopy does not implement the assignment operator. This is a violation of the Rule of Three and thus, if we were to use something like destination3 = source instead of SharedCopy destination3(source), the counter variable would not be properly decremented.

// The copying policies discussed in this chapter are the basis for a powerful concept in C++11 - smart pointers. But before we discuss these, we need to go into further detail on move semantics, which is a prerequisite you need to learn more about so you can properly understand the exclusive ownership policy as well as the Rule of Five, both of which we will discuss very soon. But before we discuss move semantics, we need to look into the concept of lvalues and rvalues in the next section.

// https://youtu.be/i25M0YmWs7Y