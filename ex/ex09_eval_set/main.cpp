#include "../../rsb.hpp"

void print_test(std::vector<std::vector<int>>& sets, std::vector<std::string>& formulas) {
    //print sets:
    for (size_t i = 0; i < sets.size(); ++i) {
        std::cout << "Set " << char('A' + i) << ": ";
        rsb::print_set(sets[i]);
        std::cout << std::endl;
    }
    std::cout << std::endl;

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

    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << std::endl << "----- 09 EVAL SET -----" << std::endl << std::endl;

    // Test cases for eval_set
    std::vector<std::vector<int>> sets = {
        {1, 2, 3},
        {2, 3, 4},
        {1, 4}
    };
    std::vector<std::string> formulas = {
        "A",
        "AB|",
        "AC&",
        "A!",
        "ABC&&",
        "AB>",
        "AC^"
    };

    print_test(sets, formulas);

    sets = {
        {},
        {1, 3, 5, 7, 9, 11, 13},
        {2, 4, 6, 8, 10, 12},
        {4, 5, 6, 7, 42},
        {7, 10, 42}
    };
    formulas = {
        "BC|",
        "BC|D|",
        "A!",
        "BC|!",
        "BD^",
        "C!"
    };

    print_test(sets, formulas);
    
    std::cout << std::endl;
    return 0;
}