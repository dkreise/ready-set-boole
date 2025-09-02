#include "inc/rsb.hpp"
#include "inc/tests.hpp"

#include <iostream>

int main() {

    tests::test_adder();
    tests::test_multiplier();
    tests::test_gray_code();
    tests::test_eval_formula();
    tests::test_truth_table();

    return 0;
}