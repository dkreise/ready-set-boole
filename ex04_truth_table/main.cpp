#include "../rsb.hpp"

void print_test(const std::string& formula) {
    
}

int main() {
    std::cout << std::endl << "----- 04 TRUTH TABLE -----" << std::endl << std::endl;

    std::vector<std::string> formulas = {
        "AB&",
        "AB|",
        "AB^",
        "A!",
        "AB>",
        "AB&C|",
        "DS|KD>&R!^",
        "ABC&"
    };

    for (const auto& formula: formulas) {
        try {
            rsb::print_truth_table(formula);
        } catch (const std::invalid_argument& e) {
            std::cout << "Formula: " << formula << " \t " << e.what() << std::endl;
        }
    }
    
    return 0;
}