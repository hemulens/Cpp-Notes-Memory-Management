#include <chrono>
#include <iostream>

int main()
{
    // create array 
    const int size = 4000;
    static int x[size][size];

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
          x[i][j] = i + j;
          //std::cout << &x[i][j] << ": i=" << i << ", j=" << j << std::endl;
      }
    }

    // print execution time to console
    auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Execution time: " << duration << " microseconds" << std::endl;

    return 0;
}


// Cache-friendly coding
// In the code sample to the right, run the code and note the results. Then please modify the code slightly by interchanging the index i and j when accessing the variable x and take a close look at the resulting runtime performance compared to the original version.

// Depending on the machine used for executing the two code versions, there will be a huge difference in execution time. In order to understand why this happens, let us revisit the memory layout we investigated with the gdb debugger at the beginning of this lesson: Even though we have created a two-dimensional array, it is stored in a one-dimensional succession of memory cells. In our minds, the array will (probably) look like this: 2-cache-memory-1.png

// In memory however, it is stored as a single line as follows: 2-cache-memory-2.png

// As can be seen, the rows of the two-dimensional matrix are copied one after the other. This format is called "row major" and is the default for both C and C++. Some other languages such as Fortran are "column major" and a memory-aware programmer should always know the memory layout of the language he or she is using.

// Note that even though the row major memory layout is used in C++, this doesn't mean that all C++ libraries have the same default; for example, the popular Eigen library used for matrix operations in C++ defaults to column major.