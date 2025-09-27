#include "../../rsb.hpp"

void check_gray_code(unsigned int n, unsigned int expected) {
    unsigned int result = rsb::gray_code(n);
    std::cout << "Gray( " << n << " ) = " << result << " (expected: " << expected << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 03 GRAY CODE -----" << std::endl << std::endl;

    check_gray_code(0, 0);
    check_gray_code(1, 1);
    check_gray_code(2, 3);
    check_gray_code(3, 2);
    check_gray_code(4, 6);
    check_gray_code(5, 7);
    check_gray_code(6, 5);
    check_gray_code(7, 4);
    check_gray_code(8, 12);
    check_gray_code(11, 14);

    std::cout << std::endl;
    return 0;
}