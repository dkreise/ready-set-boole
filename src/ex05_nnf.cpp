#include "../inc/rsb.hpp"
#include "../inc/symbols.hpp"
#include "../inc/Node.hpp"

#include <iostream>
#include <string>
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

    Node* toNNF(Node* root) {
        if (!root) {
            return nullptr;
        }

        switch (root->value) {
            case '&':
                return new Node('&', toNNF(root->left), toNNF(root->right));
            case '|':
                return new Node('|', toNNF(root->left), toNNF(root->right));
            case '!': {
                Node* child = toNNF(root->left);
                switch (child->value) {
                    case '!':
                        return child->left;
                    case '&':
                        return new Node('|', toNNF(new Node('!', child->left)), toNNF(new Node('!', child->right)));
                    case '|':
                        return new Node('&', toNNF(new Node('!', child->left)), toNNF(new Node('!', child->right)));
                    default: // variable
                        return new Node('!', child);
                }
            }
            case '^': {
                Node* left = new Node('&', toNNF(root->left), toNNF(new Node('!', root->right)));
                Node* right = new Node('&', toNNF(new Node('!', root->left)), toNNF(root->right));
                return new Node('|', left, right);
            }
            case '>':
                return new Node('|', toNNF(new Node('!', root->left)), toNNF(root->right));
            case '=': {
                Node* left = toNNF(new Node('>', root->left, root->right));
                Node* right = toNNF(new Node('>', root->right, root->left));
                return new Node('&', left, right);
            }
            default: // variable
                return root;
        }
        return root;
    }
}

namespace rsb {
    std::string negation_normal_form(const std::string& formula) {
        Node* root = buildTreeFromPRN(formula);
        // root->printTree();
        root = toNNF(root);
        // root->printTree();
        root->printRPN();
        std::cout << std::endl;
        return "";
    }
}
