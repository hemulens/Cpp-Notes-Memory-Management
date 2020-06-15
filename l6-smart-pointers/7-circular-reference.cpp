#include <iostream>
#include <memory>

class MyClass
{
public:
  std::shared_ptr<MyClass> _member;
  ~MyClass() { std::cout << "Destructor of MyClass called" << std::endl; }
};

int main()
{
  std::shared_ptr<MyClass> myClass1(new MyClass);
  std::shared_ptr<MyClass> myClass2(new MyClass);

  myClass1->_member = myClass2;  // circular references (read below)
  myClass2->_member = myClass1;

  return 0;
}


// Despite all the advantages of shared pointers, it is still possible to have problems with memory management though. Consider the scenario on the right.

// In main, two shared pointers myClass1 and myClass2 which are managing objects of type MyClass are allocated on the stack. As can be seen from the console output, both smart pointers are automatically deallocated when the scope of main ends:


// Destructor of MyClass called
// Destructor of MyClass called
// When the following two lines are added to main, the result is quite different:


// myClass1->_member = myClass2;
// myClass2->_member = myClass1;

// These two lines produce a circular reference. When myClass1 goes out of scope at the end of main, its destructor can’t clean up memory as there is still a reference count of 1 in the smart pointer, which is caused by the shared pointer _member in myClass2. The same holds true for myClass2, which can not be properly deleted as there is still a shared pointer to it in myClass1. This deadlock situation prevents the destructors from being called and causes a memory leak. When we use Valgrind on this program, we get the following summary:


// ==20360== LEAK SUMMARY:
// ==20360==    definitely lost: 16 bytes in 1 blocks
// ==20360==    indirectly lost: 80 bytes in 3 blocks
// ==20360==      possibly lost: 72 bytes in 3 blocks
// ==20360==    still reachable: 200 bytes in 6 blocks
// ==20360==         suppressed: 18,985 bytes in 160 blocks
// As can be seen, the memory leak is clearly visible with 16 bytes being marked as "definitely lost". To prevent such circular references, there is a third smart pointer, which we will look at in the following.