#include <stdio.h>

int main() {
  // initialize some variables on the stack
  int i, j, *p;

  // correct usage of lvalues and rvalues

  i = 42; // i is an lvalue and 42 is an rvalue

  p = new int;
  *p = i; // the dereferenced pointer is an lvalue
  printf("Address = %p, value = %i \n", p, *p);
  delete p; 

  ((i < 42) ? i : j) = 23; // the conditional operator returns an lvalue (either i or j)

  // incorrect usage of lvalues and rvalues
  //42 = i; // error : the left operand must be an lvalue
  //j * 42 = 23; // error : the left operand must be an lvalue

  return 0; 
}




// https://youtu.be/QCI9DixUUNk

// What are lvalues and rvalues?
// A good grasp of lvalues and rvalues in C++ is essential for understanding the more advanced concepts of rvalue references and motion semantics.

// Let us start by stating that every expression in C++ has a type and belongs to a value category. When objects are created, copied or moved during the evaluation of an expression, the compiler uses these value expressions to decide which method to call or which operator to use.

// Prior to C++11, there were only two value categories, now there are as many as five of them: [lvalues+rvalues.png]

// To keep it short, we do not want to go into all categories, but limit ourselves to lvalues and prvalues:

// Lvalues have an address that can be accessed. They are expressions whose evaluation by the compiler determines the identity of objects or functions.

// Prvalues do not have an address that is accessible directly. They are temporary expressions used to initialize objects or compute the value of the operand of an operator.

// For the sake of simplicity and for compliance with many tutorials, videos and books about the topic, let us refer to prvalues as rvalues from here on.

// The two characters l and r are originally derived from the perspective of the assignment operator =, which always expects a rvalue on the right, and which it assigns to a lvalue on the left. In this case, the l stands for left and r for right:

// int i = 42;  // lvalue = rvalue;

// With many other operators, however, this right-left view is not entirely correct. In more general terms, an lvalue is an entity that points to a specific memory location. An rvalue is usually a short-lived object, which is only needed in a narrow local scope. To simplify things a little, one could think of lvalues as named containers for rvalues.

// In the example above, the value 42 is an rvalue. It does not have a specific memory address which we know about. The rvalue is assigned to a variable i with a specific memory location known to us, which is what makes it an lvalue in this example.

// Using the address operator & we can generate an lvalue from an rvalue and assign it to another lvalue:

// int *j = &i;

// In this small example, the expression &i generates the address of i as an rvalue and assigns it to j, which is an lvalue now holding the memory location of i.

// The code on the right illustrates several examples of lvalues and rvalues: