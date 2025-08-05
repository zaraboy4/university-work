#include "./structNode.hpp"
#include <iostream>
#include <vector>

int height(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

bool isBalanced(Node* root) {
    if (!root) return true;
    return 
        isBalanced(root->left)
        && isBalanced(root->right)
        && std::abs(height(root->left) - height(root->right)) < 2;
}

int main() {
    Node* btree = new Node(9, 
                    new Node(3, 
                        new Node(1), 
                        new Node(5)), 
                    new Node(10, 
                        new Node(10), 
                        new Node(13)));
    std::cout << height(btree) << '\n';
    std::cout << (isBalanced(btree) ? "balanced" : "not balanced") << '\n';
    destruct(btree);
    return 0;
}