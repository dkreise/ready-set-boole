#include "../../rsb.hpp"

void print_powerset(const std::vector<std::vector<int>>& powerset) {
    std::cout << "[ ";
    for (const auto& subset : powerset) {
        rsb::print_set(subset);
    }
    std::cout << " ]" << std::endl;
}

void print_powerset_of_set(const std::vector<int>& set) {
    std::cout << "Powerset of ";
    rsb::print_set(set);
    std::cout << " :" << std::endl;
    std::vector<std::vector<int>> powerset = rsb::powerset(set);
    print_powerset(powerset);
}

int main() {
    std::cout << std::endl << "----- 08 POWERSET -----" << std::endl << std::endl;

    print_powerset_of_set({});               // Empty set
    print_powerset_of_set({1});              // Singleton set
    print_powerset_of_set({1, 2});           // Two-element set
    print_powerset_of_set({1, 2, 3});        // Three-element set
    print_powerset_of_set({1, 2, 3, 4});     // Four-element set

    std::cout << std::endl;
    return 0;
}