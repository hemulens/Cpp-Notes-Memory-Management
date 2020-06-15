#include <stdlib.h>
#include <iostream>

class MyClass {
  private:
    int *_number;

  public:
    MyClass() {
      std::cout << "Variable memory allocated\n";
      _number = (int *)malloc(sizeof(int));
    }
    ~MyClass() {
      std::cout << "Variable memory destroyed\n";
      free(_number);
    }
    void setNumber(int number) {
      *_number = number;
      std::cout << "Number: " << _number << "\n";
    }
};


int main() { 
  void *memory = malloc(sizeof(MyClass));
  std::cout << "memory: " << memory << "\n";
  MyClass *object = new (memory) MyClass;
  std::cout << "object: " << object << "\n";
  object->setNumber(42);

  object->~MyClass();
  free(memory);
  return 0;
}


// Optimizing Performance with placement new
// In some cases, it makes sense to separate memory allocation from object construction. Consider a case where we need to reconstruct an object several times. If we were to use the standard new/delete construct, memory would be allocated and freed unnecessarily as only the content of the memory block changes but not its size. By separating allocation from construction, we can get a significant performance increase.

// C++ allows us to do this by using a construct called placement new: With placement new, we can pass a preallocated memory and construct an object at that memory location. Consider the following code:


// void *memory = malloc(sizeof(MyClass));
// MyClass *object = new (memory) MyClass;
// The syntax new (memory) is denoted as placement new. The difference to the "conventional" new we have been using so far is that that no memory is allocated. The call constructs an object and places it in the assigned memory location. There is however, no delete equivalent to placement new, so we have to call the destructor explicitly in this case instead of using delete as we would have done with a regular call to new:


// object->~MyClass();
// free(memory); 
// Important: Note that this should never be done outside of placement new.

// In the next section, we will look at how to overload the new operator and show the performance difference between placement new and new