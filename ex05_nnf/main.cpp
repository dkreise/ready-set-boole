#include "../rsb.hpp"

int main() {
    std::cout << "NNF" << std::endl;
    rsb::negation_normal_form("PQ>!R|");
    rsb::negation_normal_form("AB&!");
    rsb::negation_normal_form("AB|!");
    rsb::negation_normal_form("P!QR!&=P>");
    
    return 0;
}