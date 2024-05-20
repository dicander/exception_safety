// This program creates a simple knapsack with a max weight.
// All items are simple integers with weights.
// All functions preserve the invariants that all weights 
// are positive and the max weight is positive.
// and ensures that the sum of all weights is less than the max weight.
// It also keeps track of all the current items weights using a vector.

#include <iostream>
#include <vector>

using namespace std;

class Knapsack {
    private:
        int max_weight;
        vector<int> items;
        int sum_weights;
    public:
        Knapsack(int max_weight): max_weight(max_weight), sum_weights(0) {
            if (max_weight <= 0) {
                throw invalid_argument("max weight must be positive");
            }
        }

        void add_item(int weight) {
            if (weight <= 0) {
                throw invalid_argument("weight must be positive");
            }
            if (sum_weights + weight > max_weight) {
                throw invalid_argument("sum of weights must be less than max weight");
            }
            items.push_back(weight);
            sum_weights += weight;
        }

        void remove_item() {
            if (items.empty()) {
                throw invalid_argument("no items to remove");
            }
            sum_weights -= items.back();
            items.pop_back();
        }

        int get_max_weight() noexcept {
            return max_weight;
        }

        int read_weight_of_item(int index) {
            if (index < 0 || index >= items.size()) {
                throw invalid_argument("index out of bounds");
            }
            return items[index];
        }

        int get_sum_weights() noexcept {
            return sum_weights;
        }

        int get_num_items() noexcept {
            return items.size();
        }

        void print_items() noexcept {
            for (int i = 0; i < items.size(); i++) {
                cout << items[i] << " ";
            }
            cout << endl;
        }

        ~Knapsack() noexcept {
            cout << "Destructor called" << endl;
        }
};


int main() {
    Knapsack knapsack(10);
    knapsack.add_item(3);
    knapsack.add_item(4);
    knapsack.add_item(2);
    knapsack.print_items();
    cout << "Sum of weights: " << knapsack.get_sum_weights() << endl;
    cout << "Max weight: " << knapsack.get_max_weight() << endl;
    cout << "Number of items: " << knapsack.get_num_items() << endl;
    knapsack.remove_item();
    knapsack.print_items();
    cout << "Sum of weights: " << knapsack.get_sum_weights() << endl;
    cout << "Max weight: " << knapsack.get_max_weight() << endl;
    cout << "Number of items: " << knapsack.get_num_items() << endl;
    return 0;
}
