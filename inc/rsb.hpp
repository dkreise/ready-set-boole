#pragma once

#include "../inc/symbols.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdexcept>
#include <algorithm>

namespace rsb {
    unsigned int adder(unsigned int a, unsigned int b);
    unsigned int multiplier(unsigned int a, unsigned int b);
    unsigned int gray_code(unsigned int n);
    bool eval_formula(const std::string& formula);
    void print_truth_table(const std::string& formula);
    std::string negation_normal_form(const std::string& formula);
    std::string conjunctive_normal_form(const std::string& formula);
    bool sat(const std::string& formula);
    std::vector<std::vector<int>> powerset(const std::vector<int>& set);
    std::vector<int> eval_set(const std::string& formula, const std::vector<std::vector<int>> sets);
}
