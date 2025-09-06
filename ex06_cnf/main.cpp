#include "../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 06 CNF -----" << std::endl << std::endl;

    std::vector<std::string> formulas = {
        "AB&",
        "AB|",
        "AA!&",
        "PQ>!R|",
        "AB^",
        "AB&!",
        "AB|!",
        "AB&C|",
        "AB|C&",
        "AB|C|D|",
        "AB&C&D&",
        "AB&!C!|",
        "AB|!C!&",
        "P!QR!&=P>",
        "DS|KD>&R!^"
    };

    std::cout << std::left << std::setw(20) << "Formula";
    std::cout << std::left << std::setw(40) << "CNF" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& formula : formulas) {
        std::string result = rsb::conjunctive_normal_form(formula);

        std::cout << std::left << std::setw(20) << formula;
        std::cout << std::left << std::setw(40) << result << std::endl;
    }

    std::cout << std::endl;
    return 0;
}