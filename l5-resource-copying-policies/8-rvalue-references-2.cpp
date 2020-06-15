#include <iostream>

int main()
{
  int i = 1; 
  int j = 2; 
  int k = i + j; 
  int &&l = i + j;

  std::cout << "k = " << k << ", l = " << l << std::endl;
  // std::cout << "Address of l = " << &l << std::endl;

  return 0; 
}


// Since C++11, there is a new type available called rvalue reference, which can be identified from the double ampersand && after a type name. With this operator, it is possible to store and even modify an rvalue, i.e. a temporary object which would otherwise be lost quickly.

// But what do we need this for? Before we look into the answer to this question, let us consider the example on the right.

// Outro
// https://youtu.be/3cKhShD1lD4