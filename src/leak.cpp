#include <iostream>

int main() {
    int* v = new int[10];
    for (int i = 0; i < 10; i++) {
        v[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        std::cout << v[i] << std::endl;
    }
    return 0;
}