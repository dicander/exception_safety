// This program has a base class and a derived class. The derived class inherits from the base class
// and the constructor attempts to swallow an exception thrown by the base class constructor

#include <iostream>

class Base {
public:
    Base() {
        throw std::runtime_error("Base constructor threw an exception");
    }
};


class Derived : public Base {
public:
    Derived() {
        try {
            Base();
        } catch (std::exception& e) {
            std::cout << "Caught exception in Derived constructor: " << e.what() << std::endl;
        }
    }
};


int main() {
    Derived d;
    return 0;
}