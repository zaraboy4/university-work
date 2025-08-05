#include "./structNode.hpp"
#include <iostream>
#include <vector>


int minNode(Node* root) {
    while (root->left)
        root = root->left;
    return root->data;
}

int maxNode(Node* root) {
    while (root->right)
        root = root->right;
    return root->data;
}

bool isBST(Node* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (!root->left && root->right) 
        return isBST(root->right) && root->data < minNode(root->right);
    if (!root->right && root->left) 
        return isBST(root->left) && maxNode(root->left) <= root->data;
    return 
        isBST(root->left) && isBST(root->right)
        && maxNode(root->left) <= root->data && root->data < minNode(root->right);   
}

int main() {
    Node* btree = new Node(9, 
                    new Node(3, 
                        new Node(1), 
                        new Node(5)), 
                    new Node(10, 
                        new Node(10), 
                        new Node(13)));
    std::cout << (isBST(btree) ? "bst" : "not bst") << '\n';
    destruct(btree);
    return 0;
}