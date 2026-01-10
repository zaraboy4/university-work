#include <iostream>

template <class T>
struct TreeNode {
    T data;
    TreeNode *left, *right;
    TreeNode(const T& _data, TreeNode* _left = nullptr, TreeNode* _right = nullptr)
        : data(_data), left(_left), right(_right)
    {}
};

template <class T>
void destruct(TreeNode<T>* root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->right);
    delete root;
}

template <class T>
void print(TreeNode<T>* root) {
    if (!root) {
        std::cout << "()";
        return;
    }
    std::cout << '(' << root->data << ' ';
    print(root->left);
    std::cout << ' ';
    print(root->right);
    std::cout << ')';
}

template <class T>
TreeNode<T>** searchHelper(TreeNode<T>*& root, const T& el) {
    TreeNode<T>** ptr = &root;
    while (*ptr && (*ptr)->data != el) {
        if (el < (*ptr)->data) {
            ptr = &(*ptr)->left;
        }
        else {
            ptr = &(*ptr)->right;
        }
    }
    return ptr;
}

template <class T>
bool search(TreeNode<T>* root, const T& el) {
    return *searchHelper(root, el) != nullptr;
}

template <class T>
bool insert(TreeNode<T>*& root, const T& el) {
    TreeNode<T>** toAdd = searchHelper(root, el);
    if (*toAdd) {
        return false; 
    }
    *toAdd = new TreeNode<T>(el);
    return true;
}

template <class T>
bool remove(TreeNode<T>*& root, const T& el) {
    TreeNode<T>** toRemove = searchHelper(root, el);
    TreeNode<T>* dummy = *toRemove;
    if (*toRemove == nullptr) {
        return false;
    }
    if (!(*toRemove)->left) {
        *toRemove = (*toRemove)->right;
        delete dummy;
        return true;
    }
    if (!(*toRemove)->right) {
        *toRemove = (*toRemove)->left;
        delete dummy;
        return true;
    }
    TreeNode<T>** minRight = &(*toRemove)->right;
    while ((*minRight)->left) {
        minRight = &(*minRight)->left;
    }
    TreeNode<T>* minRightNode = *minRight;
    *minRight = (*minRight)->right;
    minRightNode->left = (*toRemove)->left;
    minRightNode->right = (*toRemove)->right;
    delete dummy;
    *toRemove = minRightNode;
    // (*toRemove)->data = (*minRight)->data;
    // TreeNode<T>* temp = *minRight;
    // *minRight = (*minRight)->right;
    // delete temp;
    return true;
}

int main() {
    TreeNode<int>* root = new TreeNode<int>(6,
                                new TreeNode<int>(3,
                                    new TreeNode<int>(1),
                                    new TreeNode<int>(4)),
                                new TreeNode<int>(10,
                                    new TreeNode<int>(7,
                                        nullptr,
                                        new TreeNode<int>(8,
                                            nullptr,
                                            new TreeNode<int>(9))),
                                    new TreeNode<int>(15)));
    std::cout << search(root, 1);
    print(root);
    std::cout << "remove: " << remove(root, 6) << '\n';
    std::cout << root->data << '\n';
    print(root);
    std::cout << "remove: " << remove(root, 3) << '\n';
    std::cout << root->data << '\n';
    print(root);
    std::cout << "remove: " << remove(root, 7) << '\n';
    std::cout << root->data << '\n';
    print(root);
    destruct(root);
    return 0;
}