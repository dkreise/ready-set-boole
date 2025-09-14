#include "../../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 09 EVAL SET -----" << std::endl << std::endl;

    // Test cases for eval_set
    std::vector<std::vector<int>> sets = {
        {1, 2, 3},
        {2, 3, 4},
        {1, 4}
    };

    //print sets:
    for (size_t i = 0; i < sets.size(); ++i) {
        std::cout << "Set " << char('A' + i) << ": ";
        rsb::print_set(sets[i]);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::string> formulas = {
        "A",
        "AB|",
        "AC&",
        "A!",
        "ABC&&",
        "AB>",
        "AC^"
    };

    std::cout << std::left << std::setw(20) << "Formula";
    std::cout << std::left << std::setw(40) << "Result" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& formula : formulas) {
        std::cout << std::left << std::setw(20) << formula;
        try {
            std::vector<int> result = rsb::eval_set(formula, sets);
            rsb::print_set(result);
            std::cout << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << std::left << std::setw(40) << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
    return 0;
}