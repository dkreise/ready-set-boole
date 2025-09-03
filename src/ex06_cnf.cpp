#include "../inc/rsb.hpp"
#include "../inc/tests.hpp"
#include "../inc/Node.hpp"
#include "../inc/symbols.hpp"

#include <iostream>
#include <stack>

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

    Node* buildTreeFromPRN(const std::string& formula) {
        std::stack<Node*> nodes;
        for (size_t i = 0; i < formula.length(); i++) {
            char c = formula[i];
            SymbolType type = get_symbol_type(c);
            switch (type) {
                case VARIABLE:
                    nodes.push(new Node(c));
                    break;
                case UNARY_OPERATOR:
                    if (nodes.empty()) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for unary operation.");
                    }
                    {
                        Node* operand = nodes.top();
                        nodes.pop();
                        nodes.push(new Node(c, operand));
                    }
                    break; 
                case BINARY_OPERATOR:
                    if (nodes.size() < 2) {
                        throw std::invalid_argument("Error: Invalid formula. Not enough characters for binary operation.");
                    }
                    {
                        Node* right = nodes.top();
                        nodes.pop();
                        Node* left = nodes.top();
                        nodes.pop();
                        nodes.push(new Node(c, left, right));
                    }
                    break;
                default:
                    throw std::invalid_argument("Error: Invalid character in the formula.");
            }
        }
        if (nodes.size() != 1) {
            throw std::invalid_argument("Error: Invalid formula. Not unique value in the end.");
        }
        return nodes.top();
    }

    Node* toCNF(Node* root) {
        if (!root) {
            return nullptr;
        }

        switch (root->value) {
            case '&':
                return new Node('&', toCNF(root->left), toCNF(root->right));
            case '|': {
                Node* left = toCNF(root->left);
                Node* right = toCNF(root->right);
                if (left->value == '&') {
                    // (A & B) | C = (A | C) & (B | C)
                    Node* newLeft = toCNF(new Node('|', left->left, right));
                    Node* newRight = toCNF(new Node('|', left->right, right));
                    return new Node('&', newLeft, newRight);
                }
                if (right->value == '&') {
                    // A | (B & C) = (A | B) & (A | C)
                    Node* newLeft = toCNF(new Node('|', left, right->left));
                    Node* newRight = toCNF(new Node('|', left, right->right));
                    return new Node('&', newLeft, newRight);
                }
                return new Node('|', left, right);
            }
            default: // variable or !
                return root;
        }
    }
}

namespace rsb {
    std::string conjunctive_normal_form(const std::string& formula) {
        std::string nnf = rsb::negation_normal_form(formula);
        Node* root = buildTreeFromPRN(nnf);
        root = toCNF(root);
        std::string rpn = root->getRPN();
        std::cout << "Formula: " << formula << "   ->   " << rpn << std::endl;
        return rpn;
    }
}
