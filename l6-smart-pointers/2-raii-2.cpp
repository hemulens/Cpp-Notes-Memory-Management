#include <iostream>

class MyInt
{
  int *_p; // pointer to heap data
  public:
    MyInt(int *p = NULL) // http://www.stroustrup.com/bs_faq2.html#null
    {
      std::cout << "resource " << *_p << " at memory address " << _p << " allocated" << std::endl;
      _p = p;
    }
    ~MyInt()
    {
      std::cout << "resource " << *_p << " deallocated" << std::endl;
      delete _p;
    }
    int &operator*() // overload dereferencing operator
    {
      // std::cout << "resource " << *_p << " at memory address " << _p << " dereferenced" << std::endl;
      return *_p;
    }
};

int main()
{
  double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (size_t i = 0; i < 5; ++i)
  {
    // allocate the resource on the heap
    MyInt *en = new MyInt(new int(i));  // segmentation fault -> The destructor of MyInt would never be called, hence causing a memory leak with each loop iteration.

    // use the resource
    std::cout << **en << "/" << den[i] << " = " << **en / den[i] << std::endl;

    return 0;
  }
}

