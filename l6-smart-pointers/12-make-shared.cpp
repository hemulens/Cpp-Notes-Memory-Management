// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-make_shared

#include <memory>
#include <iostream>

std::shared_ptr<int> p1 { new int{2} }; // bad
auto p = std::make_shared<int>(2);    // good

int main() {
  std::cout << p1 << std::endl;
  std::cout << p << std::endl;
}

// Reason If you first make an object and then give it to a shared_ptr constructor, you (most likely) do one more allocation (and later deallocation) than if you use make_shared() because the reference counts must be allocated separately from the object.