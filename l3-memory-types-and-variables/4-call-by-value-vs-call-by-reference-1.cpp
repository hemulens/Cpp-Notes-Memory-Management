bool MyLocalFunction(int myInt) {
	bool isBelowThreshold = myInt < 42 ? true : false;
	return isBelowThreshold;
}

int main() {
	bool res = MyLocalFunction(23);
	return 0; 
}

// Variable Scopes in C++
// The time between allocation and deallocation is called the lifetime of a variable. Using a variable after its lifetime has ended is a common programming error, against which most modern languages try to protect: Local variables are only available within their respective scope (e.g. inside a function) and are simply not available outside - so using them inappropriately will result in a compile-time error. When using pointer variables however, programmers must make sure that allocation is handled correctly and that no invalid memory addresses are accessed.

// The example to the right shows a set of local (or automatic) variables, whose lifetime is bound to the function they are in.

// When MyLocalFunction is called, the local variable isBelowThreshold is allocated on the stack. When the function exits, it is again deallocated.

// For the allocation of local variables, the following holds:

// Memory is allocated for local variables only after a function has been called. The parameters of a function are also local variables and they are initialized with a value copied from the caller.

// As long as the current thread of execution is within function A, memory for the local variables remains allocated. This even holds true in case another function B is called from within the current function A and the thread of execution moves into this nested function call. However, within function B, the local variables of function A are not known.

// When the function exits, its locals are deallocated and there is now way to them afterwards - even if the address were still known (e.g. by storing it within a pointer).

// Let us briefly revisit the most common ways of passing parameters to a function, which are called pass-by-reference and pass-by-value.

// Quiz : How many local variables?¶
// How many local variables are created within the scope of MyLocalFunction?