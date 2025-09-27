#include "../../rsb.hpp"

int main() {
    std::cout << std::endl << "----- 05 NNF -----" << std::endl << std::endl;

    std::vector<std::string> formulas = {
        "AB&!",
        "AB|!",
        "AB>",
        "AB=",
        "AB|C&!",
        "AB&",
        "AB|",
        "AA!&",
        "PQ>!R|",
        "AB^",
        "AB&C|",
        "AB|C&",
        "AB|C|D|",
        "AB&C&D&",
        "AB&!C!|",
        "AB|!C!&",
        "P!QR!&=P>",
        "DS|KD>&R!^",
        "ABC"
    };

    std::cout << std::left << std::setw(20) << "Formula";
    std::cout << std::left << std::setw(40) << "NNF" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& formula : formulas) {
        std::cout << std::left << std::setw(20) << formula;
        
        try {
            std::string result = rsb::negation_normal_form(formula);
            std::cout << std::left << std::setw(40) << result << std::endl;
        }  catch (const std::invalid_argument& e) {
            std::cout << std::left << std::setw(40) << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
    return 0;
}