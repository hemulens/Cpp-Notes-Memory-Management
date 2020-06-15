#include <iostream>

void myFunction(int &&val)
{
  std::cout << "val = " << val << std::endl;
}

int main()
{
  myFunction(42);

  int i = 23; 
  myFunction(std::move(i)); // move says int i won't be used in the scope of main anymore

  // std::cout << "val = " << val << std::endl;
  return 0; 
}


// https://youtu.be/s6IJqVOQN0A

// Rvalue references and std::move
// In order to fully understand the concept of smart pointers in the next lesson, we first need to take a look at a powerful concept introduced with C++11 called move semantics.

// The last section on lvalues, rvalues and especially rvalue references is an important prerequisite for understanding the concept of moving data structures.

// Let us consider the function on the right which takes an rvalue reference as its parameter.

// The important message of the function argument of myFunction to the programmer is : The object that binds to the rvalue reference &&val is yours, it is not needed anymore within the scope of the caller (which is main). As discussed in the previous section on rvalue references, this is interesting from two perspectives:

// Passing values like this improves performance as no temporary copy needs to be made anymore and
// ownership changes, since the object the reference binds to has been abandoned by the caller and now binds to a handle which is available only to the receiver. This could not have been achieved with lvalue references as any change to the object that binds to the lvalue reference would also be visible on the caller side.


// There is one more important aspect we need to consider: rvalue references are themselves lvalues. While this might seem confusing at first glance, it really is the mechanism that enables move semantics: A reference is always defined in a certain context (such as in the above example the variable val) . Even though the object it refers to (the number 42) may be disposable in the context it has been created (the main function), it is not disposable in the context of the reference . So within the scope of myFunction, val is an lvalue as it gives access to the memory location where the number 42 is stored.

// Note however that in the above code example we cannot pass an lvalue to myFunction, because an rvalue reference cannot bind to an lvalue. The code


// int i = 23;
// myFunction(i)
// would result in a compiler error. There is a solution to this problem though: The function std::move converts an lvalue into an rvalue (actually, to be exact, into an xvalue, which we will not discuss here for the sake of clarity), which makes it possible to use the lvalue as an argument for the function:


// int i = 23; 
// myFunction(std::move(i));
// In doing this, we state that in the scope of main we will not use i anymore, which now exists only in the scope of myFunction. Using std::move in this way is one of the components of move semantics, which we will look into shortly. But first let us consider an example of the Rule of Three.