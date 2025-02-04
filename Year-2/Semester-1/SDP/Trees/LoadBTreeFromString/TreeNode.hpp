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

Node* extractMin(Node*& root) {
    if (root->left) {
        return extractMin(root->left);
    }
    Node* n = root;
    root = root->right;
    return n;
}

bool remove(Node*& root, const int& el) {
    if (!root) return false;
    if (root->data == el) {
        Node* detach = root;
        if (!root->left) root = root->right;
        else if (!root->right) root = root->left;
        else {
            Node* n = extractMin(root->right);
            n->left = root->left;
            n->right = root->right;
            root = n;
        }
        delete detach;
        return true;
    }
    return remove(el < root->data ? root->left : root->right, el);
}
