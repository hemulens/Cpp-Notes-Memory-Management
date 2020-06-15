#include <iostream>
#include <string>
#include <memory>

class MyClass {
  private:
    std::string _text;  // lives on the stack or on the heap?

  public:
    MyClass() {}
    MyClass(std::string text) {
      _text = text;
    }
    ~MyClass() {
      std::cout << _text << " destroyed" << std::endl;
    }
    void setText(std::string text) {
      _text = text;
    }
};

int main() {
  // Create unique pointer to proprietary class
  std::unique_ptr<MyClass> myClass1(new MyClass());  // myClass1 lives on the stack, but the instance of "new MyClass()" which is managed by this pointer (myClass1) lives on the heap.
  std::unique_ptr<MyClass> myClass2(new MyClass("String 2"));

  // Call member function using ->
  myClass1->setText("String 1");

  // Use the dereference operator *
  *myClass1 = *myClass2;  // deep copy here

  // Use .get() function to retrieve a raw pointer to the object (stack or heap? Maybe a course mistake? Should be heap)
  std::cout << "Objects have heap addresses " << myClass1.get() << " and " << myClass2.get() << std::endl;
  // Added by me to check
  std::cout << "Objects' reference addresses " << &myClass1 << " and " << &myClass2 << std::endl;
}



// In the example now on the right, we will construct a unique pointer to a custom class. Also, we will see how the standard -> and * operators can be used to access member functions of the managed object, just as we would with a raw pointer:

// Note that the custom class MyClass has two constructors, one without arguments and one with a string to be passed, which initializes a member variable _text that lives on the stack. Also, once an object of this class gets destroyed, a message to the console is printed, along with the value of _text. In main, two unique pointers are created with the address of a MyClass object on the heap as arguments. With myClass2, we can see that constructor arguments can be passed just as we would with raw pointers. After both pointers have been created, we can use the -> operator to access members of the class, such as calling the function setText. From looking at the function call alone you would not be able to tell that myClass1 is in fact a smart pointer. Also, we can use the dereference operator * to access the value of myClass1 and myClass2 and assign the one to the other. Finally, the . operator gives us access to proprietary functions of the smart pointer, such as retrieving the internal raw pointer with get().

// The console output of the program looks like the following:

// Objects have stack addresses 0x1004000e0 and 0x100400100
// String 2 destroyed
// String 2 destroyed
// Obviously, both pointers have different addresses on the stack, even after copying the contents from myClass2 to myClass1. As can be seen from the last two lines of the output, the destructor of both objects gets called automatically at the end of the program and - as expected - the value of the internal string is identical due to the copy operation.

// Summing up, the unique pointer allows a single owner of the underlying internal raw pointer. Unique pointers should be the default choice unless you know for certain that sharing is required at a later stage. We have already seen how to transfer ownership of a resource using the Rule of Five and move semantics. Internally, the unique pointer uses this very concept along with RAII to encapsulate a resource (the raw pointer) and transfer it between pointer objects when either the move assignment operator or the move constructor are called. Also, a key feature of a unique pointer, which makes it so well-suited as a return type for many functions, is the possibility to convert it to a shared pointer. We will have a deeper look into this in the section on ownership transfer.


// Igor's answer (Mentor):

// Hi Sergei,

// so the get() method will return you indeed an address from the heap. What I feel might be a bit confusing here is that you have on the one hand the pointers like myClass1 that are indeed living on the stack and then you have the objects they are referencing that are living on the heap. What is important to keep in mind is that whenever you are creating an object via new, which is here the case for the object that is referenced by the pointer, you will have memory allocated on the heap. You can also see that by the addresses printed out, the addresses returned by the get method, that are referencing the objects on the heap, are way lower compared to the addresses of the pointers themselves, as the stack is growing from larger address spaces downwards whereas the heap is growing upwards. This is also quite nicely to see from your print output, as in the one case the addresses are ascending, in the other case descending.

// Profile image
// Igor K
// Mentor

// 16 minutes ago