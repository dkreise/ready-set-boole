#include "inc/rsb.hpp"
#include "inc/tests.hpp"

#include <iostream>

int main() {

    tests::test_adder();
    tests::test_multiplier();
    tests::test_gray_code();
    tests::test_eval_formula();
    tests::test_truth_table();

    rsb::negation_normal_form("PQ>!R|");
    rsb::negation_normal_form("AB&!");
    rsb::negation_normal_form("AB|!");
    rsb::negation_normal_form("P!QR!&=P>");

    return 0;
}