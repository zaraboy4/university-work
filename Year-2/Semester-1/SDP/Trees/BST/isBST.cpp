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

    return 0;
}