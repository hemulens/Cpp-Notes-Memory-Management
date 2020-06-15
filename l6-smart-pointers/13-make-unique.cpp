// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-make_unique

#include <memory>
#include <iostream>

std::unique_ptr<int> p1 { new int{2} }; // ok
auto p = std::make_unique<int>(2);    // good

int main() {
  std::cout << p1 << std::endl;
  std::cout << p << std::endl;

  std::cout << "Unique smart pointer's heap address is " << p.get() << std::endl;
}

// Reason For convenience and consistency with shared_ptr.