#pragma once

#include <iostream>

class Node {
    public:
        char value;
        Node* left;
        Node* right;

        Node(char val, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) {}

        ~Node() {
            delete left;
            delete right;
        }

        void printTree(int space = 0) {
            // if (this == nullptr) {
            //     return;
            // }
            space += 4;
            if (right) {
                right->printTree(space);
            }
            // std::cout << std::endl;
            for (int i = 0; i < space; i++) {
                std::cout << " ";
            }
            std::cout << value << "\n";
            if (left) {
                left->printTree(space);
            }
        }

        void printRPN() {
            if (left) {
                left->printRPN();
            }
            if (right) {
                right->printRPN();
            }
            std::cout << value;
        }

        std::string getRPN() {
            std::string rpn;
            if (left) {
                rpn += left->getRPN();
            }
            if (right) {
                rpn += right->getRPN();
            }
            rpn += value;
            return rpn;
        }
};