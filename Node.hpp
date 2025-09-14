#pragma once

#include <iostream>
#include <memory>

class Node {
    public:
        char value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(char v) : value(v), left(nullptr), right(nullptr) {}
        Node(char v, std::unique_ptr<Node> l) : value(v), left(std::move(l)), right(nullptr) {}
        Node(char v, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
            : value(v), left(std::move(l)), right(std::move(r)) {}

        // ~Node() {
        //     delete left;
        //     delete right;
        // }

        std::unique_ptr<Node> clone() const {
            auto newNode = std::make_unique<Node>(value);
            if (left) newNode->left = left->clone();
            if (right) newNode->right = right->clone();
            return newNode;
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