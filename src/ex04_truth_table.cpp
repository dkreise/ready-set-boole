#include "../inc/rsb.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

namespace {
    std::vector<char> extract_variables(const std::string& input) {
        std::unordered_set<char> var_set;
        for (char c : input) {
            if (c >= 'A' && c <= 'Z') {
                var_set.insert(c);
            }
        }
        std::vector<char> variables(var_set.begin(), var_set.end());
        std::sort(variables.begin(), variables.end());
        return variables;
    }

    void print_table_header(std::vector<char>& vars, int n) {
        std::cout << "|";
        for (char v : vars) {
            std::cout << " " << v << " |";
        }
        std::cout << " = |" << std::endl;
        std::cout << "|";
        for (int i = 0; i < n; i++) {
            std::cout << "---|";
        }
        std::cout << "---|" << std::endl;
    }

    void print_table_row(std::vector<int> values, bool result) {
        std::cout << "|";
        for (int v : values) {
            std::cout << " " << v << " |";
        }
        std::cout << " " << (result ? "1" : "0") << " |" << std::endl;
    }

    std::string get_new_formula(const std::string& input, std::vector<char>& vars, std::vector<int>& values) {
        std::string new_formula;
        for (char c : input) {
            if (c >= 'A' && c <= 'Z') {
                int idx = std::find(vars.begin(), vars.end(), c) - vars.begin();
                new_formula += (values[idx] ? '1' : '0');
            } else {
                new_formula += c;
            }
        }
        return new_formula;
    }

    void print_test(const std::string& formula) {
        try {
            rsb::print_truth_table(formula);
        } catch (const std::invalid_argument& e) {
            std::cout << "Formula: " << formula << " \t " << e.what() << std::endl;
        }
    }
}

namespace rsb {
    void print_truth_table(const std::string& input) {
        std::cout << "Truth Table for: " << input << std::endl << std::endl;

        std::vector<char> vars = extract_variables(input);
        int n = vars.size();

        print_table_header(vars, n);

        int num_combinations = 1 << n;  // 2^n 
        for (int mask = 0; mask < num_combinations; mask++) {
            std::vector<int> values(n);
            for (int i = 0; i < n; i++) {  // bitmasks 0 .. (2^n - 1), bit i tells whether vars[i] is 0 or 1
                values[i] = (mask >> (n - i - 1)) & 1; // ex. mask = 101, we are moving right, just to compare with 1 the i-th bit
            }
        

            std::string new_formula = get_new_formula(input, vars, values);

            // Evaluate the new formula
            bool result = eval_formula(new_formula);
            print_table_row(values, result);
        }
        std::cout << std::endl;
    }
}

namespace tests {
    void test_truth_table() {
        std::cout << std::endl << "----- 04 TRUTH TABLE -----" << std::endl;

        print_test("AB&");
        print_test("AB|");
        print_test("AB^");
        print_test("A!");
        print_test("AB>");
        print_test("AB&C|");
        print_test("DS|KD>&R!^");
    }
}
