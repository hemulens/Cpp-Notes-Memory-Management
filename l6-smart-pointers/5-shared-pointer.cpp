#include <iostream>
#include <memory>

int main()
{
  std::shared_ptr<int> shared1(new int);
  std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

  {
    std::shared_ptr<int> shared2 = shared1;
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;
  }

  std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

  return 0;
}

// The Shared Pointer
// Just as the unique pointer, a shared pointer owns the resource it points to. The main difference between the two smart pointers is that shared pointers keep a reference counter on how many of them point to the same memory resource. Each time a shared pointer goes out of scope, the counter is decreased. When it reaches zero (i.e. when the last shared pointer to the resource is about to vanish). the memory is properly deallocated. This smart pointer type is useful for cases where you require access to a memory location on the heap in multiple parts of your program and you want to make sure that whoever owns a shared pointer to the memory can rely on the fact that it will be accessible throughout the lifetime of that pointer.

// The following diagram illustrates the basic idea of a shared pointer: [shared-pointer.png]

// Please take a look at the code on the right.

// We can see that shared pointers are constructed just as unique pointers are. Also, we can access the internal reference count by using the method use_count(). In the inner block, a second shared pointer shared2 is created and shared1 is assigned to it. In the copy constructor, the internal resource pointer is copied to shared2 and the resource counter is incremented in both shared1 and shared2. Let us take a look at the output of the code:


// shared pointer count = 1
// shared pointer count = 2
// shared pointer count = 1
// You may have noticed that the lifetime of shared2 is limited to the scope denoted by the enclosing curly brackets. Thus, once this scope is left and shared2 is destroyed, the reference counter in shared1 is decremented by one - which is reflected in the three console outputs given above.