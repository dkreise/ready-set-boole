#include "../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 07 SAT -----" << std::endl;

    std::vector<std::string> formulas = {
        "AB&",
        "AB|",
        "AA!&",
        "AA^",
        "AB^",
        "A!",
        "AB>",
        "AB&C|",
        "DS|KD>&R!^"
    };

    for (const auto& formula : formulas) {
        bool result = rsb::sat(formula);
        std::cout << "Formula: " << formula << " \t SAT: " << (result ? "True" : "False") << std::endl;
    }
    
    return 0;
}