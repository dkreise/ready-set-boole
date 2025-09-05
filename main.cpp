#include "inc/rsb.hpp"
#include "inc/tests.hpp"

#include <iostream>

int main() {

    tests::test_adder();
    tests::test_multiplier();
    tests::test_gray_code();
    tests::test_eval_formula();
    tests::test_truth_table();

    std::cout << "NNF" << std::endl;
    rsb::negation_normal_form("PQ>!R|");
    rsb::negation_normal_form("AB&!");
    rsb::negation_normal_form("AB|!");
    rsb::negation_normal_form("P!QR!&=P>");

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

    tests::test_sat();
    tests::test_powerset();
    tests::test_eval_set();
    tests::test_map();
    // tests::test_reverse_map();

    return 0;
}
