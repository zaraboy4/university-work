#pragma once
#include <iostream>

struct Node {
    Node(const int& d = int(), Node* l = nullptr, Node* r = nullptr)
        : data(d), left(l), right(r) {}
    int data;
    Node* left;
    Node* right;
};

void destruct(Node*& root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->right);
    delete root;
    root = nullptr;
}

void print(Node* root) {
    if (!root) return;
    print(root->left);
    std::cout << root->data << ' ';
    print(root->right);
}