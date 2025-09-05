#include "../rsb.hpp"

void check_gray_code(unsigned int n, unsigned int expected) {
    unsigned int result = rsb::gray_code(n);
    std::cout << " " << n << " (gray) = " << result << " (expected: " << expected << ")" << std::endl;
}

int main() {
    std::cout << std::endl << "----- 03 GRAY CODE -----" << std::endl;

    check_gray_code(0, 0);
    check_gray_code(1, 1);
    check_gray_code(2, 3);
    check_gray_code(3, 2);
    check_gray_code(4, 5);
    check_gray_code(5, 4);

    return 0;
}