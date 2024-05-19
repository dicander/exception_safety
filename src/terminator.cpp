// This program ends abruptly with std::terminate

#include <iostream>
#include <exception>

int main() {
    std::terminate();
    return 0;
}