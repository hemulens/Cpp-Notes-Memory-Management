// Passing Variables by Value
// When calling a function as in the previous code example, its parameters (in this case myInt) are used to create local copies of the information provided by the caller. The caller is not sharing the parameter with the function but instead a proprietary copy is created using the assignment operator = (more about that later). When passing parameters in such a way, it is ensured that changes made to the local copy will not affect the original on the caller side. The upside to this is that inner workings of the function and the data owned by the caller are kept neatly separate.

// However, there are two major downsides to this:

// Passing parameters by value means that a copy is created, which is an expensive operation that might consume large amounts of memory, depending on the data that is being transferred. Later in this course we will encounter "move semantics", which is an effective way to compensate for this downside.
// Passing by value also means that the created copy can not be used as a back channel for communicating with the caller, for example by directly writing the desired information into the variable.
// Consider the example on the right in the pass_by_value.cpp file. In main, the integer val is initialized with 0. When passing it to the function AddTwo, a local copy of val is created, which only exists within the scope of AddTwo, so the add-operation has no effect on val on the caller side. So when main returns, val has a value of 2 instead of 4.


#include <iostream>

void AddTwo(int val) {
    val += 2;
}

int main() {
    int val = 0;
    AddTwo(val);
    val += 2;

    std::cout << "val = " << val << std::endl;
 
    return 0;
}