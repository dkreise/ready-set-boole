#include "../rsb.hpp"

void check_adder(unsigned int a, unsigned int b, unsigned int expected) {
    unsigned int result = rsb::adder(a, b);
    std::cout << " " << a << " + " << b << " = " << result << " (expected: " << expected << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 01 ADDER -----" << std::endl;

    check_adder(1, 1, 2);
    check_adder(0, 3, 3);
    check_adder(4, 5, 9);
    check_adder(10, 15, 25);
    check_adder(13, 8, 21);
    check_adder(42, 119, 161);
    
    return 0;
}