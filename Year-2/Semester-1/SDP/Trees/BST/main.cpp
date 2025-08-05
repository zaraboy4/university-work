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

void toVector(Node* root, std::vector<int>& list) {
    if (!root) return;
    toVector(root->left, list);
    list.push_back(root->data);
    toVector(root->right, list);
}

Node* toBSTNaive(const std::vector<int>& xs) {
    Node* res = nullptr;
    for (int x : xs) insert(res, x);
    return res;
}

void toBSTRec(Node*& root, const std::vector<int>& xs, int l, int r) {
    if (l > r) return;
    int m = (l + r) / 2;
    root = new Node(xs[m]);
    toBSTRec(root->left, xs, l, m - 1);
    toBSTRec(root->right, xs, m + 1, r);
}

Node* toBalancedBST(const std::vector<int>& xs) {
    Node* res = nullptr;
    toBSTRec(res, xs, 0, xs.size() - 1);
    return res;
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
    std::cout << height(btree) << '\n';
    std::cout << (isBalanced(btree) ? "balanced" : "not balanced") << '\n';

    std::cout << "elements: \n";
    std::vector<int> list;
    toVector(btree, list);
    for (int l : list)
        std::cout << l << ' ';
    std::cout << '\n';
    
    Node* btree2 = toBSTNaive(list);
    std::cout << (isBST(btree2) ? "bst" : "not bst") << '\n';
    std::cout << height(btree2) << '\n';
    std::cout << (isBalanced(btree2) ? "balanced" : "not balanced") << '\n';

    list.push_back(14);
    Node* btree3 = toBalancedBST(list);
    std::cout << (isBST(btree3) ? "bst" : "not bst") << '\n';
    std::cout << height(btree3) << '\n';
    std::cout << (isBalanced(btree3) ? "balanced" : "not balanced") << '\n';
    destruct(btree);
    destruct(btree2);
    destruct(btree3);
    return 0;
}