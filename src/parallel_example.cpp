#include <iostream>
#include <optional>
#include <future>
#include <execution>
#include <vector>

// Independent operations that can be parallelized
std::optional<int> compute_a(int x) {
    return x + 10;
}

std::optional<int> compute_b(int x) {
    return x * 2;
}

std::optional<int> compute_c(int x) {
    return x - 5;
}

// Function to combine results
std::optional<int> combine_results(const std::vector<std::optional<int>>& results) {
    int sum = 0;
    for (const auto& result : results) {
        if (result.has_value()) {
            sum += result.value();
        } else {
            return std::nullopt;
        }
    }
    return sum;
}

int main() {
    int initial_value = 42;

    // Launch parallel tasks
    std::vector<std::future<std::optional<int>>> futures;
    futures.push_back(std::async(std::launch::async, compute_a, initial_value));
    futures.push_back(std::async(std::launch::async, compute_b, initial_value));
    futures.push_back(std::async(std::launch::async, compute_c, initial_value));

    // Gather results
    std::vector<std::optional<int>> results;
    for (auto& future : futures) {
        results.push_back(future.get());
    }

    // Combine results
    auto final_result = combine_results(results).value_or(0);

    std::cout << final_result << std::endl;

    return 0;
}
