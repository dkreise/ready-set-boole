#include "../rsb.hpp"

void print_result(double n) {
    try {
        auto [x, y] = rsb::reverse_map(n);
        std::cout << "reverse_map(" << n << ") = (" << x << ", " << y << ")" << std::endl;  
    }
    catch (const std::out_of_range& e) {
        std::cout << "reverse_map(" << n << ") threw exception: " << e.what() << std::endl;
    }
}

int main() {
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
    
    return 0;
}