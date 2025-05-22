// This program has a class with a constructor that throws an exception after some
// but not all variables have been set. We want to see what happens. Does the program
// crash? Does the destructor get called? Does the memory get cleaned up?

#include <iostream>
#include <string>
#include <stdexcept>

struct MyClass {
    MyClass(int a, int b, int c) : a(a), b(b) {
        if (c == 0) {
            throw std::runtime_error("c cannot be 0");
        }
        this->c = c;
    }

    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
    }
    int a;
    int b;
    int c;
};

// Main should attempt to read the partially constructed object after it has been constructed.
int main() {
    MyClass* myClass = nullptr;
    try {
        myClass = new MyClass(1, 2, 0);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << myClass->a << std::endl;
    //flush cout
    std::cout << std::flush;
    std::cout << myClass->b << std::endl;
    std::cout << std::flush;
    std::cout << myClass->c << std::endl;
    std::cout << std::flush;
    delete myClass;
    return 0;
}
