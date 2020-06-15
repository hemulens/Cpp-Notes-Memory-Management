#include <iostream>

void AddFive(int &v, bool &b) {
  v += 5;
  b = true;
}

int main() {
    int val = 0;
    bool success = false;
    AddFive(val, success);
    val += 2;

    std::cout << "val = " << val << ", success = " << success << std::endl;
 
    return 0;
}


// Quiz : Modifying several parameters¶
// An additional advantage of passing variables by reference is the possibility to modify several variables. When using the function return value for such a purpose, returning several variables is usually very cumbersome.

// Your task here is to create a function AddFive that modifies the int input variable by adding 5 and modifies the bool input variable to be true. In the code to the right you will find the function call in main().