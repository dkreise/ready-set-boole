#include "../rsb.hpp"

void print_test(const std::string& formula) {
    try {
        bool result = rsb::eval_formula(formula);
        std::cout << "Formula: " << formula << " \t Result: ";
        if (result) {
            std::cout << "True" << std::endl;
        } else {
            std::cout << "False" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Formula: " << formula << " \t " << e.what() << std::endl;
    }
}

int main() {
    std::cout << std::endl << "----- 04 EVAL FORMULA -----" << std::endl;

    print_test("1");
    print_test("10&");
    print_test("10|");
    print_test("11>");
    print_test("10=");
    print_test("1011||=");
    print_test("1011||=0>");
    print_test("!0");
    print_test("1>10");
    print_test("02+");
    print_test("1!1|0");
    
    return 0;
}