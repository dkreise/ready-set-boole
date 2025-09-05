#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"

namespace {
    uint32_t convert_to_morton(uint16_t n) {
        uint32_t res = n;
        res = (res | (res << 8)) & 0x00FF00FF; // 00000000111111110000000011111111
        res = (res | (res << 4)) & 0x0F0F0F0F; // 00001111000011110000111100001111
        res = (res | (res << 2)) & 0x33333333; // 00110011001100110011001100110011
        res = (res | (res << 1)) & 0x55555555; // 01010101010101010101010101010101
        return res;
    }

    void print_result(uint16_t x, uint16_t y) {
        try {
            double result = rsb::map(x, y);
            std::cout << "map(" << x << ", " << y << ") = " << result << std::endl;  
        }
        catch (const std::out_of_range& e) {
            std::cout << "map(" << x << ", " << y << ") threw exception: " << e.what() << std::endl;
        }
    }
}

namespace rsb {
    double map(uint16_t x, uint16_t y) {

        uint32_t x_morton = convert_to_morton(x);
        uint32_t y_morton = convert_to_morton(y);
        uint32_t morton_code = x_morton | (y_morton << 1);

        double norm = static_cast<double>(morton_code) / static_cast<double>(UINT32_MAX);
        return norm;
    }
}

namespace tests{
    void test_map() {
        std::cout<<std::endl << "Testing rsb::map..." << std::endl;
        // Test corners
        print_result(0, 0);
        print_result(65535, 0);
        print_result(0, 65535);
        print_result(65535, 65535);

        // Test midpoints
        print_result(16384, 16384);
        print_result(16384, 572); 
        print_result(10000, 20000);
        print_result(30000, 40000);
        print_result(50000, 60000);
    }
}
