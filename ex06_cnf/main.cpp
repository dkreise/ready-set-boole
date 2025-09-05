#include "../rsb.hpp"

int main() {
    std::cout << std::endl << "CNF" << std::endl;
    rsb::conjunctive_normal_form("PQ>!R|");
    rsb::conjunctive_normal_form("AB&!");
    rsb::conjunctive_normal_form("AB|!");
    rsb::conjunctive_normal_form("AB|C&");
    rsb::conjunctive_normal_form("AB|C|D|");
    rsb::conjunctive_normal_form("AB&C&D&");
    rsb::conjunctive_normal_form("AB&!C!|");
    rsb::conjunctive_normal_form("AB|!C!&");
    rsb::conjunctive_normal_form("P!QR!&=P>");

    return 0;
}