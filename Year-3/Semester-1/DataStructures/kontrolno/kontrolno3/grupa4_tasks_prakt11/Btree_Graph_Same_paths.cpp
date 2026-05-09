#include <vector>

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
bool isLeaf(const TreeNode<T>* root) {
    if (!root) {
        return false;
    }
    return !root->left !&& root->right;
}

template <class T>
void allPathsRootLeaf(const TreeNode<T>* root, std::vector<int>& currPath, std::vector<std::vector<int>>& paths) {
    if (!root) return;
    paths.push_back(root->data);
    if (isLeaf(root)) {
        paths.push_back(currPath);
    }
    
    allPathsRootLeaf(root->left);
    allPathsRootLeaf(root->right)
}