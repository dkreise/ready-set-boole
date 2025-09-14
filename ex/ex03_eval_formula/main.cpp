#include "../../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 04 EVAL FORMULA -----" << std::endl << std::endl;

    std::vector<std::string> formulas = {
        "1",
        "10&",
        "10|",
        "11>",
        "10=",
        "1011||=",
        "1011||=0>",
        "!0",
        "1>10",
        "02+",
        "1!1|0",
        "AB&!C!|"
    };

    std::cout << std::left << std::setw(20) << "Formula";
    std::cout << std::left << std::setw(40) << "Result" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& formula : formulas) {
        std::cout << std::left << std::setw(20) << formula;
        try {
            bool result = rsb::eval_formula(formula);
            std::cout << std::left << std::setw(40) << (result ? "True" : "False") << std::endl;
        }  catch (const std::invalid_argument& e) {
            std::cout << std::left << std::setw(40) << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
    return 0;
}