// Passing smart pointers to functions
// Let us consider the following recommendation of the C++ guidelines on smart pointers:

// R. 30 : Take smart pointers as parameters only to explicitly express lifetime semantics

// The core idea behind this rule is the notion that functions that only manipulate objects without affecting its lifetime in any way should not be concerned with a particular kind of smart pointer. A function that does not manipulate the lifetime or ownership should use raw pointers or references instead. A function should take smart pointers as parameter only if it examines or manipulates the smart pointer itself. As we have seen, smart pointers are classes that provide several features such as counting the references of a shared_ptr or increasing them by making a copy. Also, data can be moved from one unique_ptr to another and thus transferring the ownership. A particular function should accept smart pointers only if it expects to do something of this sort. If a function just needs to operate on the underlying object without the need of using any smart pointer property, it should accept the objects via raw pointers or references instead.

// The following examples are pass-by-value types that lend the ownership of the underlying object:

// void f(std::unique_ptr<MyObject> ptr)

// void f(std::shared_ptr<MyObject> ptr)

// void f(std::weak_ptr<MyObject> ptr)

// Passing smart pointers by value means to lend their ownership to a particular function f. In the above examples 1-3, all pointers are passed by value, i.e. the function f has a private copy of it which it can (and should) modify. Depending on the type of smart pointer, a tailored strategy needs to be used. Before going into details, let us take a look at the underlying rule from the C++ guidelines (where "widget" can be understood as "class").