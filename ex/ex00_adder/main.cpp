#include "../rsb.hpp"

void check_adder(unsigned int a, unsigned int b) {
    unsigned int result = rsb::adder(a, b);
    std::cout << " " << a << " + " << b << " = " << result << " (expected: " << a + b << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 01 ADDER -----" << std::endl << std::endl;

    check_adder(1, 1);
    check_adder(0, 3);
    check_adder(4, 5);
    check_adder(10, 15);
    check_adder(13, 8);
    check_adder(42, 119);
    
    std::cout << std::endl;
    return 0;
}