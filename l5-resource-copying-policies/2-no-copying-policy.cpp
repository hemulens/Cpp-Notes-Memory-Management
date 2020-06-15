class NoCopyClass1
{
private:
    NoCopyClass1(const NoCopyClass1 &);
    NoCopyClass1 &operator=(const NoCopyClass1 &);

public:
    NoCopyClass1(){};
};

class NoCopyClass2
{
public:
    NoCopyClass2(){}
    NoCopyClass2(const NoCopyClass2 &) = delete;
    NoCopyClass2 &operator=(const NoCopyClass2 &) = delete;
};

int main()
{
    NoCopyClass1 original1;
    NoCopyClass1 copy1a(original1); // copy c’tor – copying fobidden
    NoCopyClass1 copy1b = original1; // assigment operator – copying fobidden

    NoCopyClass2 original2;
    NoCopyClass2 copy2a(original2); // copy c’tor – copying fobidden
    NoCopyClass2 copy2b = original2; // assigment operator – copying fobidden

    return 0;
}


// No copying policy
// The simplest policy of all is to forbid copying and assigning class instances all together. This can be achieved by declaring, but not defining a private copy constructor and assignment operator (see NoCopyClass1 below) or alternatively by making both public and assigning the delete operator (see NoCopyClass2 below). The second choice is more explicit and makes it clearer to the programmer that copying has been actively forbidden. Let us have a look at a code example on the right that illustrates both cases.

// On compiling, we get the following error messages:


// error: calling a private constructor of class 'NoCopyClass1'
//     NoCopyClass1 copy1(original1);
//     NoCopyClass1 copy1b = original1; 

// error: call to deleted constructor of 'NoCopyClass2'
//     NoCopyClass2 copy2(original2);
//     NoCopyClass2 copy2b = original2; 
// Both cases effectively prevent the original object from being copied or assigned. In the C++11 standard library, there are some classes for multi-threaded synchronization which use the no copying policy.