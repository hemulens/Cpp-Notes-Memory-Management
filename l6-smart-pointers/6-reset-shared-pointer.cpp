#include <iostream>
#include <memory>

class MyClass
{
public:
  ~MyClass() { std::cout << "Destructor of MyClass called" << std::endl; }
};

int main()
{
  std::shared_ptr<MyClass> shared(new MyClass);
  std::cout << "shared pointer count = " << shared.use_count() << std::endl;

  shared.reset(new MyClass);
  std::cout << "shared pointer count = " << shared.use_count() << std::endl;

  return 0;
}

// A shared pointer can also be redirected by using the reset() function. If the resource which a shared pointer manages is no longer needed in the current scope, the pointer can be reset to manage a difference resource as illustrated in the example on the right.

// Note that in the example, the destructor of MyClass prints a string to the console when called. The output of the program looks like the following:

// shared pointer count = 1
// Destructor of MyClass called
// shared pointer count = 1
// Destructor of MyClass called

// After creation, the program prints 1 as the reference count of shared. Then, the reset function is called with a new instance of MyClass as an argument. This causes the destructor of the first MyClass instance to be called, hence the console output. As can be seen, the reference count of the shared pointer is still at 1. Then, at the end of the program, the destructor of the second MyClass object is called once the path of execution leaves the scope of main.