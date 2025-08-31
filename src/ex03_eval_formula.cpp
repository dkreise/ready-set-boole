#include "../inc/rsb.hpp"
#include "../inc/symbols.hpp"

#include <iostream>
#include <stack>
#include <stdexcept>

namespace {
    SymbolType get_symbol_type(char ch) {
        switch (ch) {
            case '0':
            case '1':
                return BOOL;
            case '!':
                return UNARY_OPERATOR;
            case '&':
            case '|':
            case '^':
            case '>':
            case '=':
                return BINARY_OPERATOR;
            default:
                if (std::isupper(ch)) {
                    return VARIABLE;
                }
                throw std::invalid_argument("Error: Invalid character in the formula.");
        }
    }

    bool do_binary_operation(bool a, bool b, char op) {
        switch (op) {
            case '&':
                return a && b;
            case '|':
                return a || b;
            case '^':
                return a != b;
            case '>':
                return !a || b;
            case '=':
                return a == b;
            default:
                throw std::invalid_argument("Error: Invalid binary operator.");
        }
    }

    void print_test(std::string formula) {
        try {
            bool result = rsb::eval_formula(formula);
            std::cout << "Formula: " << formula << " \t Result: ";
            if (result) {
                std::cout << "True" << std::endl;
            } else {
                std::cout << "False" << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Formula: " << formula << " \t " << e.what() << std::endl;
        }
    }
}

namespace rsb {
    bool eval_formula(std::string input) {
        std::stack<bool> st;
        int len = input.length();

        for (int i = 0; i < len; i++) {
            char ch = input[i];
            SymbolType type = get_symbol_type(ch);

            switch (type) {
                case BOOL:
                    st.push(ch == '1');
                    break;
                case VARIABLE:
                    throw std::invalid_argument("Error: Invalid character in the formula.");
                    break;
                case UNARY_OPERATOR:
                    if (st.empty()) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for unary operation.");
                    }
                    st.top() = !st.top();
                    break;
                case BINARY_OPERATOR:
                    if (st.size() < 2) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for binary operation.");
                    }
                    bool b = st.top();
                    st.pop();
                    bool a = st.top();
                    st.pop();
                    st.push(do_binary_operation(a, b, ch));
                    break;
            }
        }

        if (st.size() != 1) {
            throw std::invalid_argument("Error: Invalid formula. Not unique character in the end.");
        }
        return st.top();
    }
}

namespace tests {
    void test_eval_formula() {
        std::cout << std::endl << "----- 04 EVAL FORMULA -----" << std::endl;

        print_test("1");
        print_test("10&");
        print_test("10|");
        print_test("11>");
        print_test("10=");
        print_test("1011||=");
        print_test("1011||=0>");
        print_test("!0");
        print_test("1>10");
        print_test("02+");
        print_test("1!1|0");
    }
}