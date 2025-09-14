#include "../rsb.hpp"

void print_result(uint16_t x, uint16_t y) {
    try {
        double result = rsb::map(x, y);
        std::cout << "map(" << x << ", " << y << ") = " << result << std::endl;  
    }
    catch (const std::out_of_range& e) {
        std::cout << "map(" << x << ", " << y << ") threw exception: " << e.what() << std::endl;
    }
}

int main() {
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
    
    return 0;
}