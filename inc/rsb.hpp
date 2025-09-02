#pragma once

#include <string>

namespace rsb {
    unsigned int adder(unsigned int a, unsigned int b);
    unsigned int multiplier(unsigned int a, unsigned int b);
    unsigned int gray_code(unsigned int n);
    bool eval_formula(std::string input);
    void print_truth_table(const std::string& input);
} 
