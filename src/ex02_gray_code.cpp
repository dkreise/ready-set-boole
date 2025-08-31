#include "../inc/rsb.hpp"
#include <iostream>

namespace rsb {
    unsigned int gray_code(unsigned int n) {
        return n ^ (n >> 1);
    }
}

namespace {
    void check_gray_code(unsigned int n, unsigned int expected) {
        unsigned int result = rsb::gray_code(n);
        std::cout << " " << n << " (gray) = " << result << " (expected: " << expected << ")" << std::endl;
    }
}

namespace tests {
    void test_gray_code() {
        std::cout << std::endl << "----- 03 GRAY CODE -----" << std::endl;

        check_gray_code(0, 0);
        check_gray_code(1, 1);
        check_gray_code(2, 3);
        check_gray_code(3, 2);
        check_gray_code(4, 5);
        check_gray_code(5, 4);
    }
}
