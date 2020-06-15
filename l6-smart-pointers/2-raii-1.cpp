#include <iostream>

class MyInt
{
  int *_p; // pointer to heap data
  public:
    MyInt(int *p = NULL)  // http://www.stroustrup.com/bs_faq2.html#null
    { 
      std::cout << "resource " << *_p << " at memory address " << _p << " allocated" << std::endl;
      _p = p;
    }
    ~MyInt()
    {
      std::cout << "resource " << *_p << " deallocated" << std::endl;
      delete _p;
    }
    int &operator*()  // overload dereferencing operator
    {  
      // std::cout << "resource " << *_p << " at memory address " << _p << " dereferenced" << std::endl;
      return *_p;
    }
};

int main()
{
  double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (size_t i = 0; i < 5; ++i)
  {
    // allocate the resource on the stack
    MyInt en(new int(i));  // initializes int at value of 1 on the heap, creating a pointer; deletes itself automatically (via destructor) at the end of the scope

    // use the resource
    std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
  }

  return 0;
}


// Let us now take a look at the code example on the right.

// At the beginning of the program, an array of double values den is allocated on the stack. Within the loop, a new double is created on the heap using new. Then, the result of a division is printed to the console. At the end of the loop, delete is called to properly deallocate the heap memory to which en is pointing. Even though this code is working as it is supposed to, it is very easy to forget to call delete at the end. Let us therefore use the principles of RAII to create a management class that calls delete automatically:


// class MyInt
// {
//     int *_p; // pointer to heap data
// public:
//     MyInt(int *p = NULL) { _p = p; }
//     ~MyInt() 
//     { 
//         std::cout << "resource " << *_p << " deallocated" << std::endl;
//         delete _p; 
//     }
//     int &operator*() { return *_p; } // // overload dereferencing operator
// };

// In this example, the constructor of class MyInt takes a pointer to a memory resource. When the destructor of a MyInt object is called, the resource is deleted from memory - which makes MyInt an RAII memory management class. Also, the * operator is overloaded which enables us to dereference MyInt objects in the same manner as with raw pointers. Let us therefore slightly alter our code example from above to see how we can properly use this new construct:

// int main()
// {
//     double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
//     for (size_t I = 0; I < 5; ++i)
//     {
//         // allocate the resource on the stack
//         MyInt en(new int(i));

//         // use the resource
//         std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
//     }

//     return 0;
// }
// Update the code on the right with the snippets above before proceeding.


// Let us break down the resource allocation part in two steps:

// The part new int(i) creates a new block of memory on the heap and initializes it with the value of i. The returned result is the address of the block of memory.
// The part MyInt en(…)calls the constructor of class MyInt, passing the address of a valid memory block as a parameter.
// After creating an object of class MyInt on the stack, which, internally, created an integer on the heap, we can use the dereference operator in the same manner as before to retrieve the value to which the internal raw pointer is pointing. Because the MyInt object en lives on the stack, it is automatically deallocated after each loop cycle - which automatically calls the destructor to release the heap memory. The following console output verifies this:


// 0/1 = 0
// resource 0 deallocated
// 1/2 = 0.5
// resource 1 deallocated
// 2/3 = 0.666667
// resource 2 deallocated
// 3/4 = 0.75
// resource 3 deallocated
// 4/5 = 0.8
// resource 4 deallocated

// We have thus successfully used the RAII idiom to create a memory management class that spares us from thinking about calling delete. By creating the MyInt object on the stack, we ensure that the deallocation occurs as soon as the object goes out of scope.

// https://youtu.be/eSCgbrpSNj0