#include "../rsb.hpp"

void check_multiplier(unsigned int a, unsigned int b, unsigned int expected) {
    unsigned int result = rsb::multiplier(a, b);
    std::cout << " " << a << " * " << b << " = " << result << " (expected: " << expected << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 02 MULTIPLIER -----" << std::endl;

    check_multiplier(1, 1, 1);
    check_multiplier(0, 3, 0);
    check_multiplier(4, 5, 20);
    check_multiplier(13, 15, 195);
    check_multiplier(42, 119, 4998);

    return 0;
}