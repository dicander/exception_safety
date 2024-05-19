// This code uses optionals and chains them, ignoring errors to just get the job done
// This requires C++23

#include <iostream>
#include <optional>

std::optional<int> get_int() {
    return 42;
}

std::optional<int> add_one(int x) {
    return x + 1;
}

std::optional<int> multiply_by_two(int x) {
    return x * 2;
}

int main() {
    auto result = get_int()
        .and_then(add_one)
        .and_then(multiply_by_two)
        .value_or(0);

    std::cout << result << std::endl;
    return 0;
}