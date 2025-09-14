#include "../../rsb.hpp"

void check_multiplier(unsigned int a, unsigned int b) {
    unsigned int result = rsb::multiplier(a, b);
    std::cout << " " << a << " * " << b << " = " << result << " (expected: " << a * b << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 02 MULTIPLIER -----" << std::endl << std::endl;

    check_multiplier(1, 1);
    check_multiplier(0, 3);
    check_multiplier(4, 5);
    check_multiplier(13, 15);
    check_multiplier(42, 119);

    std::cout << std::endl;
    return 0;
}