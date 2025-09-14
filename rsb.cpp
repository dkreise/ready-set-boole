#include "rsb.hpp"

namespace rsb {

    /*** EX 00 ***/

    unsigned int adder(unsigned int a, unsigned int b) {
        unsigned int carry = a & b;
        unsigned int sum = a ^ b;
        while (carry != 0) {
            unsigned int sum_without_carry = sum;
            carry = carry << 1;
            sum = sum_without_carry ^ carry;
            carry = sum_without_carry & carry;
        }
        return sum;
    }

    /*** EX 01 ***/

    unsigned int multiplier(unsigned int a, unsigned int b) {
        unsigned int result = 0u;
        while (b != 0u) {
            unsigned int bit = b & 1u;
            if (bit == 1u) {
                result = adder(result, a);
            }
            b = b >> 1;
            a = a << 1;
        }
        return result;
    }

    /*** EX 02 ***/

    unsigned int gray_code(unsigned int n) {
        return n ^ (n >> 1);
    }

    /*** EX 03 ***/

    bool eval_formula(const std::string& formula) {
        std::stack<bool> st;
        int len = formula.length();

        for (int i = 0; i < len; i++) {
            char ch = formula[i];
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

    /*** EX 04 ***/

    void print_truth_table(const std::string& formula) {
        std::cout << "Truth Table for: " << formula << std::endl << std::endl;

        std::vector<char> vars = extract_variables(formula);
        int n = vars.size();

        print_table_header(vars, n);

        int num_combinations = 1 << n;  // 2^n 
        for (int mask = 0; mask < num_combinations; mask++) {
            std::vector<int> values(n);
            bool result = evaluate_row(mask, formula, vars, values);
            print_table_row(values, result);
        }
        std::cout << std::endl;
    }

    /*** EX 05 ***/

    std::unique_ptr<Node> toNNF(std::unique_ptr<Node> root) {
        if (!root) {
            return nullptr;
        }

        switch (root->value) {
            case '&':
                return std::make_unique<Node>('&', toNNF(std::move(root->left)), toNNF(std::move(root->right)));
            case '|':
                return std::make_unique<Node>('|', toNNF(std::move(root->left)), toNNF(std::move(root->right)));
            case '!': {
                auto child = toNNF(std::move(root->left));
                if (child->value == '!') {
                    // !!A => A
                    return std::move(child->left);
                } else if (child->value == '&') {
                    // De Morgan: !(A & B) => !A | !B
                    auto left = std::make_unique<Node>('!', std::move(child->left));
                    auto right = std::make_unique<Node>('!', std::move(child->right));
                    return toNNF(std::make_unique<Node>('|', std::move(left), std::move(right)));
                } else if (child->value == '|') {
                    // De Morgan: !(A | B) => !A & !B
                    auto left = std::make_unique<Node>('!', std::move(child->left));
                    auto right = std::make_unique<Node>('!', std::move(child->right));
                    return toNNF(std::make_unique<Node>('&', std::move(left), std::move(right)));
                } else {
                    // variable
                    return std::make_unique<Node>('!', std::move(child));
                }
            }
            case '^': {
                auto leftClone = root->left->clone(); 
                auto rightClone = root->right->clone();
                auto left = std::make_unique<Node>(
                    '&', 
                    toNNF(std::move(leftClone)), 
                    toNNF(std::make_unique<Node>('!', std::move(rightClone)))
                );
                auto right = std::make_unique<Node>(
                    '&', 
                    toNNF(std::make_unique<Node>('!', std::move(root->left))), 
                    toNNF(std::move(root->right))
                );
                return std::make_unique<Node>('|', std::move(left), std::move(right));
            }
            case '>':
                return std::make_unique<Node>('|', toNNF(std::make_unique<Node>('!', std::move(root->left))), toNNF(std::move(root->right)));
            case '=': {
                auto leftClone = root->left->clone(); 
                auto rightClone = root->right->clone();
                auto left = toNNF(std::make_unique<Node>(
                    '>', 
                    std::move(leftClone), 
                    std::move(rightClone))
                );
                auto right = toNNF(std::make_unique<Node>(
                    '>', 
                    std::move(root->right), 
                    std::move(root->left))
                );
                return std::make_unique<Node>('&', std::move(left), std::move(right));
            }
            default: // variable
                return std::make_unique<Node>(root->value);
        }
        return std::make_unique<Node>(root->value);
    }

    std::string negation_normal_form(const std::string& formula) {
        auto root = buildTreeFromPRN(formula);
        auto nnfRoot = toNNF(std::move(root));

        std::string res = nnfRoot->getRPN();
        // delete root;
        // delete nnfRoot;
        return res;
    }

    /*** EX 06 ***/

    std::unique_ptr<Node> toCNF(std::unique_ptr<Node> root) {
        if (!root) {
            return nullptr;
        }

        switch (root->value) {
            case '&':
                return std::make_unique<Node>('&', toCNF(std::move(root->left)), toCNF(std::move(root->right)));
            case '|': {
                auto left = toCNF(std::move(root->left));
                auto right = toCNF(std::move(root->right));
                if (left->value == '&') {
                    // (A & B) | C = (A | C) & (B | C)
                    auto rightClone = right->clone();
                    auto newLeft = toCNF(std::make_unique<Node>('|', std::move(left->left), std::move(rightClone)));
                    auto newRight = toCNF(std::make_unique<Node>('|', std::move(left->right), std::move(right)));
                    return std::make_unique<Node>('&', std::move(newLeft), std::move(newRight));
                }
                if (right->value == '&') {
                    // A | (B & C) = (A | B) & (A | C)
                    auto leftClone = left->clone();
                    auto newLeft = toCNF(std::make_unique<Node>('|', std::move(leftClone), std::move(right->left)));
                    auto newRight = toCNF(std::make_unique<Node>('|', std::move(left), std::move(right->right)));
                    return std::make_unique<Node>('&', std::move(newLeft), std::move(newRight));
                }
                return std::make_unique<Node>('|', std::move(left), std::move(right));
            }
            case '!':
                return std::make_unique<Node>('!', toCNF(std::move(root->left)));
            default: // variable or !
                return std::make_unique<Node>(root->value);
        }
    }

    std::string conjunctive_normal_form(const std::string& formula) {
        std::string nnf = rsb::negation_normal_form(formula);
        auto root = buildTreeFromPRN(nnf);
        auto cnfRoot = toCNF(std::move(root));
        
        std::string rpn = cnfRoot->getRPN();
        // delete root;
        return rpn;
    }

    /*** EX 07 ***/

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

    /*** EX 08 ***/

    std::vector<std::vector<int>> powerset(const std::vector<int>& set) {
        std::vector<std::vector<int>> result;
        int n = set.size();
        int num_combinations = 1 << n;  // 2^n

        for (int mask = 0; mask < num_combinations; mask++) {
            std::vector<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.push_back(set[i]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }

    /*** EX 09 ***/

    std::vector<int> eval_set(const std::string& formula, const std::vector<std::vector<int>> sets) {
        std::vector<int> universe;
        for (const auto& s : sets) {
            for (int elem : s) {
                if (std::find(universe.begin(), universe.end(), elem) == universe.end()) {
                    universe.push_back(elem);
                }
            }
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

    /*** EX 10 ***/

    double map(uint16_t x, uint16_t y) {
        uint32_t x_morton = convert_to_morton(x);
        uint32_t y_morton = convert_to_morton(y);
        uint32_t morton_code = x_morton | (y_morton << 1);

        double norm = static_cast<double>(morton_code) / static_cast<double>(UINT32_MAX);
        return norm;
    }

    /*** EX 11 ***/

    std::pair<uint16_t, uint16_t> reverse_map(double n) {
        if (n < 0.0 || n > 1.0) {
            throw std::out_of_range("n must be in the range [0; 1]");
        }

        uint32_t morton_code = static_cast<uint32_t>(n * static_cast<double>(UINT32_MAX));
        uint16_t x = convert_from_morton(morton_code); // even bits
        uint16_t y = convert_from_morton(morton_code >> 1); // odd bits

        return {x, y};
    }

    /********** UTILS **********/

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

    std::unique_ptr<Node> buildTreeFromPRN(const std::string& formula) {
        std::stack<std::unique_ptr<Node>> nodes;
        for (size_t i = 0; i < formula.length(); i++) {
            char c = formula[i];
            SymbolType type = get_symbol_type(c);
            switch (type) {
                case VARIABLE:
                    nodes.push(std::make_unique<Node>(c)); // same as nodes.push(new Node(c))
                    break;
                case UNARY_OPERATOR:
                    if (nodes.empty()) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for unary operation.");
                    }
                    {
                        std::unique_ptr<Node> operand = std::move(nodes.top());
                        nodes.pop();
                        nodes.push(std::make_unique<Node>(c, std::move(operand)));
                    }
                    break; 
                case BINARY_OPERATOR:
                    if (nodes.size() < 2) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for binary operation.");
                    }
                    {
                        std::unique_ptr<Node> right = std::move(nodes.top());
                        nodes.pop();
                        std::unique_ptr<Node> left = std::move(nodes.top());
                        nodes.pop();
                        nodes.push(std::make_unique<Node>(c, std::move(left), std::move(right)));
                    }
                    break;
                default:
                    throw std::invalid_argument("Error: Invalid character in the formula.");
            }
        }
        if (nodes.size() != 1) {
            throw std::invalid_argument("Error: Invalid formula. Not unique value in the end.");
        }
        return std::move(nodes.top());
    }

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

    uint32_t convert_to_morton(uint16_t n) {
        uint32_t res = n;
        res = (res | (res << 8)) & 0x00FF00FF; // 00000000111111110000000011111111
        res = (res | (res << 4)) & 0x0F0F0F0F; // 00001111000011110000111100001111
        res = (res | (res << 2)) & 0x33333333; // 00110011001100110011001100110011
        res = (res | (res << 1)) & 0x55555555; // 01010101010101010101010101010101
        return res;
    }

    uint16_t convert_from_morton(uint32_t n) {
        n = n & 0x55555555; // keep only bits in even positions
        n = (n | (n >> 1)) & 0x33333333; 
        n = (n | (n >> 2)) & 0x0F0F0F0F; 
        n = (n | (n >> 4)) & 0x00FF00FF; 
        n = (n | (n >> 8)) & 0x0000FFFF;
        return (uint16_t)n;
    }
}