#include <stdio.h>
#include <stdlib.h>

struct MyStruct {
  int i; 
  double d; 
  char a[5];
};

int main() {
  MyStruct *p = (MyStruct*)calloc(4,sizeof(MyStruct));
  p[0].i = 1; p[0].d = 3.14159; p[0].a[0] = 'a';
}


// Until now, we have only allocated memory for a C/C++ data primitive (i.e. int). However, we can also define a proprietary structure which consists of several primitive data types and use malloc or calloc in the same manner as before:

// struct MyStruct {
//     int i; 
//     double d; 
//     char a[5];
// };

// MyStruct *p = (MyStruct*)calloc(4,sizeof(MyStruct));
// p[0].i = 1; p[0].d = 3.14159; p[0].a[0] = 'a';
// After defining the struct MyStruct which contains a number of data primitives, a block of memory four times the size of MyStruct is created using the calloc command. As can be seen, the various data elements can be accessed very conveniently.