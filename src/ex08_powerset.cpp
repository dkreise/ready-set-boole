#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"

namespace {
    void print_set(const std::vector<int>& set) {
        std::cout << "[ ";
        for (int elem : set) {
            std::cout << elem << " ";
        }
        std::cout << "]";
    }

    void print_powerset(const std::vector<std::vector<int>>& powerset) {
        std::cout << "[ ";
        for (const auto& subset : powerset) {
            print_set(subset);
        }
        std::cout << " ]" << std::endl;
    }

    void print_powerset_of_set(const std::vector<int>& set) {
        std::cout << "Powerset of ";
        print_set(set);
        std::cout << " :" << std::endl;
        std::vector<std::vector<int>> powerset = rsb::powerset(set);
        print_powerset(powerset);
    }
}

namespace rsb {
    std::vector<std::vector<int>> powerset(const std::vector<int>& set) {
        std::vector<std::vector<int>> result;
        int n = set.size();
        int num_combinations = 1 << n;  // 2^n

        for (int mask = 0; mask < num_combinations; mask++) {
            std::vector<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.push_back(set[i]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }
}

namespace tests {
    void test_powerset() {
        std::cout << std::endl << "----- 08 POWERSET -----" << std::endl;

        print_powerset_of_set({});               // Empty set
        print_powerset_of_set({1});              // Singleton set
        print_powerset_of_set({1, 2});           // Two-element set
        print_powerset_of_set({1, 2, 3});        // Three-element set
        print_powerset_of_set({1, 2, 3, 4});     // Four-element set
    }
}
