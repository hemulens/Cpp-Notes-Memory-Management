#include <iostream>
#include <memory>
#include <string>
#include <vector>

class MyClass {
  private:
    std::vector<std::unique_ptr<int>> _nodes;  // lives on the stack or on the heap?
    std::vector<int> _vector {2, 3, 4};

  public:
    MyClass() {
      std::cout << "Object created at address " << this << std::endl;
    }
    
    ~MyClass() {
      std::cout << "Object" << " destroyed" << std::endl;
    }

    void setNodes(std::vector<int> vector) {
      for (int i = 0; i < _nodes.size(); i++) {
        if (_nodes[i] != nullptr) {
          _nodes[i] = nullptr;
        }
      }
      // _nodes = {};
      for (int value : vector) {
        std::unique_ptr<int> pointer = std::make_unique<int>(value);
        _nodes.emplace_back(std::move(pointer));
      }
    }

    void printNodes() {
      for (int i = 0; i < _nodes.size(); i++) {
        std::cout << "Node address: " << _nodes[i] << ", node value " << *_nodes[i] << ", raw pointer: " << (_nodes[i]).get() << ", reference: " << &(_nodes[i]) << std::endl;
      }
      auto n = _vector.begin();
      auto k = _vector.end();
      auto j = _vector.end() - 1;
      std::cout << "First value in vector: " << *n << std::endl;
      std::cout << "Last value in vector: " << *j << std::endl;
      std::cout << "Last element (vector::end()): " << *k << std::endl;
    }
};

int main() {
  MyClass target;
  target.setNodes({2, 10, 34});
  target.printNodes();
}