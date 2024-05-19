// This program implements many numbered functions that do the same basic operation, but the way
// it communicate errors with the users is different. It uses error codes with the same type as a
// return value, it uses separate error handling functions, it uses exceptions, and it uses a
// combination of exceptions and error codes. The program also demonstrates how to use the
// std::exception class to create custom exceptions.

#include <iostream>
#include <optional>
// Error codes

enum class ErrorCode {
    Success,
    InvalidInput,
    DivisionByZero,
    NegativeValue
};

ErrorCode divide(int a, int b, int& result) {
    if (b == 0) {
        return ErrorCode::DivisionByZero;
    }
    if (a < 0 || b < 0) {
        return ErrorCode::NegativeValue;
    }
    result = a / b;
    return ErrorCode::Success;
}

void handleErrorCode(ErrorCode errorCode) {
    switch (errorCode) {
        case ErrorCode::Success:
            std::cout << "Success" << std::endl;
            break;
        case ErrorCode::InvalidInput:
            std::cout << "Invalid input" << std::endl;
            break;
        case ErrorCode::DivisionByZero:
            std::cout << "Division by zero" << std::endl;
            break;
        case ErrorCode::NegativeValue:
            std::cout << "Negative value" << std::endl;
            break;
    }
}

// Error handling functions

bool divide(int a, int b, int& result, ErrorCode& errorCode) {
    if (b == 0) {
        errorCode = ErrorCode::DivisionByZero;
        return false;
    }
    if (a < 0 || b < 0) {
        errorCode = ErrorCode::NegativeValue;
        return false;
    }
    result = a / b;
    errorCode = ErrorCode::Success;
    return true;
}

// Exceptions

class DivisionByZeroException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Division by zero";
    }
};

class NegativeValueException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Negative value";
    }
};

int divide_with_exceptions(int a, int b) {
    if (b == 0) {
        throw DivisionByZeroException();
    }
    if (a < 0 || b < 0) {
        throw NegativeValueException();
    }
    return a / b;
}

// Exceptions and error codes

bool divide_error_code_parameter(int a, int b, int& result, ErrorCode& errorCode) {
    try {
        result = divide_with_exceptions(a, b);
        errorCode = ErrorCode::Success;
        return true;
    } catch (const DivisionByZeroException&) {
        errorCode = ErrorCode::DivisionByZero;
        return false;
    } catch (const NegativeValueException&) {
        errorCode = ErrorCode::NegativeValue;
        return false;
    }
}

// Optionals were introcuded in C++17, here is an example:



std::optional<int> divide_optional(int a, int b) {
    if (b == 0) {
        return std::nullopt;
    }
    if (a < 0 || b < 0) {
        return std::nullopt;
    }
    return a / b;
}

// You can also return a pair of the result and the error code:

std::pair<int, ErrorCode> divide_pair(int a, int b) {
    if (b == 0) {
        return {0, ErrorCode::DivisionByZero};
    }
    if (a < 0 || b < 0) {
        return {0, ErrorCode::NegativeValue};
    }
    return {a / b, ErrorCode::Success};
}

// Finally let's call the functions, one by one:

int main() {
    int result;
    ErrorCode errorCode;

    // Error codes
    handleErrorCode(divide(10, 2, result));
    handleErrorCode(divide(10, 0, result));
    handleErrorCode(divide(-10, 2, result));

    // Error handling functions
    if (divide(10, 2, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }
    if (divide(10, 0, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }
    if (divide(-10, 2, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }

    // Exceptions
    try {
        std::cout << divide_with_exceptions(10, 2) << std::endl;
        std::cout << divide_with_exceptions(10, 0) << std::endl;
        std::cout << divide_with_exceptions(-10, 2) << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Exceptions and error codes
    if (divide_error_code_parameter(10, 2, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }
    if (divide_error_code_parameter(10, 0, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }
    if (divide_error_code_parameter(-10, 2, result, errorCode)) {
        std::cout << "Result: " << result << std::endl;
    } else {
        handleErrorCode(errorCode);
    }

    // Optionals
    if (auto result = divide_optional(10, 2)) {
        std::cout << "Result: " << *result << std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }
    if (auto result = divide_optional(10, 0)) {
        std::cout << "Result: " << *result << std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }
    if (auto result = divide_optional(-10, 2)) {
        std::cout << "Result: " << *result << std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }

    // Pair
    auto [result1, errorCode1] = divide_pair(10, 2);
    if (errorCode1 == ErrorCode::Success) {
        std::cout << "Result: " << result1 << std::endl;
    } else {
        handleErrorCode(errorCode1);
    }
    auto [result2, errorCode2] = divide_pair(10, 0);
    if (errorCode2 == ErrorCode::Success) {
        std::cout << "Result: " << result2 << std::endl;
    } else {
        handleErrorCode(errorCode2);
    }
    auto [result3, errorCode3] = divide_pair(-10, 2);
    if (errorCode3 == ErrorCode::Success) {
        std::cout << "Result: " << result3 << std::endl;
    } else {
        handleErrorCode(errorCode3);
    }

    return 0;
}