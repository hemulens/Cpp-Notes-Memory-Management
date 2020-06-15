#include <iostream>

void myFunction(int &val)
{
  std::cout << "val = " << val << std::endl;
}

int main()
{
  int j = 42;
  myFunction(j);

  myFunction(42); // won't work

  int k = 23; 
  myFunction(j+k);  // won't work

  return 0; 
}


// Rvalue references
// You already know that an rvalue is a temporary expression which is - among other use-cases, a means of initializing objects. In the call int i = 42, 42 is the rvalue.

// Let us consider an example similar to the last one, shown on the right.

// As before, the function myFunction takes an lvalue reference as its argument. In main, the call myFunction(j) works just fine while myFunction(42) as well as myFunction(j+k) produces the following compiler error on Mac:

// candidate function not viable: expects an l-value for 1st argument

// and the following error in the workspace with g++:

// error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

// While the number 42 is obviously an rvalue, with j+k things might not be so obvious, as j and k are variables and thus lvalues. To compute the result of the addition, the compiler has to create a temporary object to place it in - and this object is an rvalue.


// Since C++11, there is a new type available called rvalue reference, which can be identified from the double ampersand && after a type name. With this operator, it is possible to store and even modify an rvalue, i.e. a temporary object which would otherwise be lost quickly.

// But what do we need this for? Before we look into the answer to this question, let us consider the example on the right.