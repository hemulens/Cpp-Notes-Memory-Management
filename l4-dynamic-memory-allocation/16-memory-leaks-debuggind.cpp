int main() {
  int *pInt = new int[10];
  // delete[] pInt;

  return 0;
}

// brew install --HEAD https://raw.githubusercontent.com/sowson/valgrind/master/valgrind.rb

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./valgrind-out.txt ./a.out
// cat valgrind-out.txt

// -> see heap summary and leak summary

// https://youtu.be/y0m_6V8fvzA
// *** https://youtu.be/K2PQTpldoIw


// Even experienced developers sometimes make mistakes that cannot be discovered at first glance. Instead of spending a lot of time searching, it makes sense for C and C++ programmers to use helper tools to perform automatic analyses of their code.

// In this section, we will look at Valgrind, a free software for Linux and Mac that is able to automatically detect memory. Windows programers can for example use the Visual Studio debugger and C Run-time Library (CRT) to detect and identify memory leaks. More information on how to do this can be found here: Find memory leaks with the CRT Library - Visual Studio | Microsoft Docs

// With recent versions of MacOS, occasional difficulties have been reported with installing Valgrind. A working version for MacOS Mojave can be downloaded from GitHub via Homebrew: GitHub - sowson/valgrind: Experimental Version of Valgrind for macOS 10.14.6 Mojave

// Valgrind is a framework that facilitates the development of tools for the dynamic analysis of programs. Dynamic analysis examines the behavior of a program at runtime, in contrast to static analysis, which often checks programs for various criteria or potential errors at the source code level before, during, or after translation. More information on Valgrind can be found here: Valgrind: About

// The Memcheck tool within Valgrind can be used to detect typical errors in programs written in C or C++ that occur in connection with memory management. It is probably the best-known tool in the Valgrind suite, and the name Valgrind is often used as a synonym for Memcheck.

// The following code generates a memory leak as the integer array has been allocated on the heap but the deallocation has been forgotten by the programmer: [remote workspace code]

// The array of integers on the heap to which pInt is pointing has a size of 10 * sizeof(int), which is 40 bytes. Let us now use Valgrind to search for this leak.

// After compiling the memory_leaks_debugging.cpp code file on the right to a.out, the terminal can be used to start Valgrind with the following command:

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=/home/workspace/valgrind-out.txt /home/workspace/a.out
// Let us look at the call parameters one by one:

// --leak-check : Controls the search for memory leaks when the client program finishes. If set to summary, it says how many leaks occurred. If set to full, each individual leak will be shown in detail.

// --show-leak-kinds : controls the set of leak kinds to show when —leak-check=full is specified. Options are definite, indirect, possible reachable, all and none

// --track-origins : can be used to see where uninitialised values come from.

// You can read the file into the terminal with:

// cat valgrind-out.txt

// *** https://youtu.be/K2PQTpldoIw


// In the following, a (small) excerpt of the valgrind-out.txt log file is given:

// ==952== 40 bytes in 1 blocks are definitely lost in loss record 18 of 45

// ...

// ==952==    by 0x10019A377: operator new(unsigned long) (in /usr/lib/libc++abi.dylib)

// ...

// ==952==    by 0x100000F8A: main (memory_leaks_debugging.cpp:12)

// ...

// ==952== LEAK SUMMARY:
// ==952==    definitely lost: 40 bytes in 1 blocks
// ==952==    indirectly lost: 0 bytes in 0 blocks
// ==952==      possibly lost: 72 bytes in 3 blocks
// ==952==    still reachable: 200 bytes in 6 blocks
// ==952==         suppressed: 18,876 bytes in 160 blocks
// As expected, the memory leak caused by the omitted deletion of the array of 10 integers in the code sample above shows up in the leak summary. Additionally, the exact position where the leak occurs in the code (line 12) can also be seen together with the responsible call with caused the leak.

// This short introduction into memory leak search is only an example of how powerful analysis tools such as Valgrind can be used to detect memory-related problems in your code.

// outro: https://youtu.be/IhFaPswyBJI