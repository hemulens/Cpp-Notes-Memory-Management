#include <stdio.h>

int main() {
  char str1[]= "UDACITY";
  printf("%s",str1);

  return 0;
}


// lldb a.out
// b debugger.cpp:4
// run
// step
// p str1
// p &str1
// x/7tb 0x00007ffeefbff900
// x/7xb 0x00007ffeefbff900

// x/1xb 0x00007ffeefbff900
// x/1xb 0x00007ffeefbff901
// x/1xb 0x00007ffeefbff902

// an offset of 1 in a hexadecimal address corresponds to an offset of 8 bits (or 1 byte) in computer memory

// https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf
// https://youtu.be/Spj2jK1-uIE
// https://youtu.be/Lopa5WXR1uQ