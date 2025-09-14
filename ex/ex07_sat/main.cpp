#include "../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 07 SAT -----" << std::endl << std::endl;

    std::vector<std::string> formulas = {
        "AB&",
        "AB|",
        "AA!&",
        "AA^",
        "AB^",
        "A!",
        "AB>",
        "AB&C|",
        "DS|KD>&R!^",
        "ABC&"
    };

    std::cout << std::left << std::setw(20) << "Formula";
    std::cout << std::left << std::setw(40) << "SAT" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& formula : formulas) {
        std::cout << std::left << std::setw(20) << formula;
        try {
            bool result = rsb::sat(formula);
            std::cout << std::left << std::setw(40) << (result ? "True" : "False") << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << std::left << std::setw(40) << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
    return 0;
}