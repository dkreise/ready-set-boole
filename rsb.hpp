#pragma once

#include "Node.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <limits>
#include <unordered_set>

enum SymbolType {
    BOOL,
    VARIABLE,
    UNARY_OPERATOR,
    BINARY_OPERATOR
};

namespace rsb {

    /*** EXERCISES ***/

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
    double map(uint16_t x, uint16_t y);
    std::pair<uint16_t, uint16_t> reverse_map(double n);

    /*** UTILS ***/
    
    SymbolType get_symbol_type(char ch);
    bool do_binary_operation(bool a, bool b, char op);
    std::vector<char> extract_variables(const std::string& formula);
    void print_table_header(std::vector<char>& vars, int n);
    void print_table_row(std::vector<int> values, bool result);
    std::string get_new_formula(const std::string& formula, std::vector<char>& vars, std::vector<int>& values);
    bool evaluate_row(int mask, const std::string& formula, std::vector<char>& vars, std::vector<int>& values);

    Node* buildTreeFromPRN(const std::string& formula);
    Node* toNNF(Node* root);
    Node* toCNF(Node* root);

    std::vector<int> set_union(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> set_intersection(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> set_difference(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> set_symmetric_difference(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> set_complement(const std::vector<int>& a, const std::vector<int>& universe);
    std::vector<int> set_implication(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe);
    std::vector<int> set_equivalence(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe);
    std::vector<int> do_binary_set_operation(char op, std::vector<int> a, std::vector<int> b, const std::vector<int>& universe);
    void print_set(const std::vector<int>& set);

    uint32_t convert_to_morton(uint16_t n);
    uint16_t convert_from_morton(uint32_t n);
}
