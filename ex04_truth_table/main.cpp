#include "../rsb.hpp"

void print_test(const std::string& formula) {
    try {
        rsb::print_truth_table(formula);
    } catch (const std::invalid_argument& e) {
        std::cout << "Formula: " << formula << " \t " << e.what() << std::endl;
    }
}

int main() {
    std::cout << std::endl << "----- 04 TRUTH TABLE -----" << std::endl;

    print_test("AB&");
    print_test("AB|");
    print_test("AB^");
    print_test("A!");
    print_test("AB>");
    print_test("AB&C|");
    print_test("DS|KD>&R!^");
    
    return 0;
}