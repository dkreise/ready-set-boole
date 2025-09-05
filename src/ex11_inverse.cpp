#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"

namespace {
    uint16_t convert_from_morton(uint32_t n) {
        n = n & 0x55555555; // keep only bits in even positions
        n = (n | (n >> 1)) & 0x33333333; 
        n = (n | (n >> 2)) & 0x0F0F0F0F; 
        n = (n | (n >> 4)) & 0x00FF00FF; 
        n = (n | (n >> 8)) & 0x0000FFFF;
        return (uint16_t)n;
    }

    void print_result(double n) {
        try {
            auto [x, y] = rsb::reverse_map(n);
            std::cout << "reverse_map(" << n << ") = (" << x << ", " << y << ")" << std::endl;  
        }
        catch (const std::out_of_range& e) {
            std::cout << "reverse_map(" << n << ") threw exception: " << e.what() << std::endl;
        }
    }
}

namespace rsb {
    std::pair<uint16_t, uint16_t> reverse_map(double n) {
        if (n < 0.0 || n > 1.0) {
            throw std::out_of_range("n must be in the range [0; 1]");
        }
        uint32_t morton_code = static_cast<uint32_t>(n * static_cast<double>(UINT32_MAX) + 0.5); // rounding to nearest integer

        uint16_t x = convert_from_morton(morton_code); // even bits
        uint16_t y = convert_from_morton(morton_code >> 1); // odd bits

        return {x, y};
    }
}

namespace tests {
    void test_reverse_map() {
        std::cout<<std::endl << "Testing rsb::reverse_map..." << std::endl;

        // Test corners
        print_result(0.0);
        print_result(0.5);
        print_result(1.0); 

        // Test midpoints
        print_result(0.1875); 
        print_result(0.1); 
        print_result(0.3);
        print_result(0.6);
        print_result(0.9);

        // Test out of range
        print_result(-0.1);
        print_result(42);
    }
}
