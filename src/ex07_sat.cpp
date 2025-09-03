#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

namespace {
    std::vector<char> extract_variables(const std::string& formula) {
        std::unordered_set<char> var_set;
        for (char c : formula) {
            if (c >= 'A' && c <= 'Z') {
                var_set.insert(c);
            }
        }
        std::vector<char> variables(var_set.begin(), var_set.end());
        std::sort(variables.begin(), variables.end());
        return variables;
    }

    std::string get_new_formula(const std::string& formula, std::vector<char>& vars, std::vector<int>& values) {
        std::string new_formula;
        for (char c : formula) {
            if (c >= 'A' && c <= 'Z') {
                int idx = std::find(vars.begin(), vars.end(), c) - vars.begin();
                new_formula += (values[idx] ? '1' : '0');
            } else {
                new_formula += c;
            }
        }
        return new_formula;
    }

    bool evaluate_row(int mask, const std::string& formula, std::vector<char>& vars, std::vector<int>& values) {
        int n = vars.size();
        for (int i = 0; i < n; i++) {  // bitmasks 0 .. (2^n - 1), bit i tells whether vars[i] is 0 or 1
            values[i] = (mask >> (n - i - 1)) & 1; // ex. mask = 101, we are moving right, just to compare with 1 the i-th bit
        }
    
        std::string new_formula = get_new_formula(formula, vars, values);
        bool result = rsb::eval_formula(new_formula);
        return result;
    }
}

namespace rsb {
    bool sat(const std::string& formula) {
        std::vector<char> vars = extract_variables(formula);
        int n = vars.size();

        int num_combinations = 1 << n;  // 2^n 
        for (int mask = 0; mask < num_combinations; mask++) {
            std::vector<int> values(n);
            bool result = evaluate_row(mask, formula, vars, values);
            if (result) {
                return true;
            }
        }
        return false;
    }
}

namespace tests {
    void test_sat() {
        std::cout << std::endl << "----- 07 SAT -----" << std::endl;

        std::vector<std::string> formulas = {
            "AB&",
            "AB|",
            "AA!&",
            "AA^",
            "AB^",
            "A!",
            "AB>",
            "AB&C|",
            "DS|KD>&R!^"
        };

        for (const auto& formula : formulas) {
            bool result = rsb::sat(formula);
            std::cout << "Formula: " << formula << " \t SAT: " << (result ? "True" : "False") << std::endl;
        }
    }
}
