#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"

namespace {
    // a U b
    std::vector<int> set_union(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> result = a;
        for (int elem : b) {
            if (std::find(result.begin(), result.end(), elem) == result.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    // a ∩ b
    std::vector<int> set_intersection(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> result;
        for (int elem : a) {
            if (std::find(b.begin(), b.end(), elem) != b.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    // a - b, a without b
    std::vector<int> set_difference(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> result;
        for (int elem : a) {
            if (std::find(b.begin(), b.end(), elem) == b.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    // a xor b
    std::vector<int> set_symmetric_difference(const std::vector<int>& a, const std::vector<int>& b) {
        return set_union(set_difference(a, b), set_difference(b, a));
    }

    // !a
    std::vector<int> set_complement(const std::vector<int>& a, const std::vector<int>& universe) {
        return set_difference(universe, a);
    }

    // a -> b = !a | b
    std::vector<int> set_implication(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
        return set_union(set_complement(a, universe), b);
    }

    // a <-> b = (a -> b) & (b -> a)
    std::vector<int> set_equivalence(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
        return set_intersection(set_implication(a, b, universe), set_implication(b, a, universe));
    }

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

    std::vector<int> do_binary_set_operation(char op, std::vector<int> a, std::vector<int> b, const std::vector<int>& universe) {
        switch (op) {
            case '&':
                return set_intersection(a, b);
            case '|':
                return set_union(a, b);
            case '^':
                return set_symmetric_difference(a, b);
            case '>':
                return set_implication(a, b, universe);
            case '=':
                return set_equivalence(a, b, universe);
            default:
                throw std::invalid_argument("Error: Invalid binary operator.");
        }
    }

    void print_set(const std::vector<int>& set) {
        std::cout << "[ ";
        for (int elem : set) {
            std::cout << elem << " ";
        }
        std::cout << "]";
    }

    void print_eval_set_result(const std::string& formula, const std::vector<std::vector<int>> sets) {
        std::vector<int> result = rsb::eval_set(formula, sets);
        std::cout << "Formula: " << formula << " \t Result: ";
        print_set(result);
        std::cout << std::endl;
    }
}

namespace rsb {
    std::vector<int> eval_set(const std::string& formula, const std::vector<std::vector<int>> sets) {
        std::vector<int> universe;
        for (const auto& s : sets) {
            universe.insert(universe.end(), s.begin(), s.end());
        }

        std::stack<std::vector<int>> st;

        for (char c : formula) {
            SymbolType type = get_symbol_type(c);
            switch (type) {
                case VARIABLE: {
                    int index = c - 'A';
                    if (index < 0 || index >= static_cast<int>(sets.size())) {
                        throw std::invalid_argument("Error: Variable index out of range.");
                    }
                    st.push(sets[index]);
                    break;
                }
                case UNARY_OPERATOR: {
                    if (st.empty()) {
                        throw std::invalid_argument("Error: Stack is empty.");
                    }
                    std::vector<int> operand = st.top();
                    st.pop();
                    std::vector<int> result = set_complement(operand, universe);
                    st.push(result);
                    break;
                }
                case BINARY_OPERATOR: {
                    if (st.size() < 2) {
                        throw std::invalid_argument("Error: Not enough elements in the stack for binary operation.");
                    }
                    std::vector<int> right = st.top();
                    st.pop();
                    std::vector<int> left = st.top();
                    st.pop();
                    std::vector<int> result = do_binary_set_operation(c, left, right, universe);
                    st.push(result);
                    break;
                }
                default:
                    throw std::invalid_argument("Error: Invalid character in the formula.");
            }
        }

        if (st.size() != 1) {
            throw std::invalid_argument("Error: Invalid formula. Not unique value in the end.");
        }
        return st.top();
    }
}

namespace tests {
    void test_eval_set() {
        // Test cases for eval_set
        std::vector<std::vector<int>> sets = {
            {1, 2, 3},
            {2, 3, 4},
            {1, 4}
        };

        //print sets:
        for (size_t i = 0; i < sets.size(); ++i) {
            std::cout << "Set " << char('A' + i) << ": ";
            print_set(sets[i]);
            std::cout << std::endl;
        }

        print_eval_set_result("A", sets); 
        print_eval_set_result("AB|", sets);
        print_eval_set_result("AC&", sets);
        print_eval_set_result("A!", sets);
        print_eval_set_result("ABC&&", sets);
        print_eval_set_result("AB>", sets);
        print_eval_set_result("AC^", sets);
    }
}
