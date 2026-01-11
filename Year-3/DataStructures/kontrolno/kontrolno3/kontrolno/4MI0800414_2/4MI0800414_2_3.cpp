#include <iostream>
#include <vector>
#include <map>

template <class T>
struct BinTreeNode {
    T data;
    BinTreeNode *left, *right;
    BinTreeNode(const T& _data, BinTreeNode* _left = nullptr, BinTreeNode* _right = nullptr)
        : data(_data), left(_left), right(_right)
    {}
};

template <class T>
void destruct(BinTreeNode<T>* root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->right);
    delete root;
}

template <class T>
void elementsAtLevel(BinTreeNode<T>* root, unsigned currLevel, unsigned targetLevel, std::vector<T>& list) {
    if (!root) return;
    if (currLevel == targetLevel) {
        list.push_back(root->data);
        return;
    }
    elementsAtLevel(root->left, currLevel + 1, targetLevel, list);
    elementsAtLevel(root->right, currLevel + 1, targetLevel, list);
}

template <class T>
int getSum(std::vector<T>& xs) {
    int sum = 0;
    for (const T& x : xs) {
        sum += x;
    }
    return sum;
}

template <class T>
unsigned height(BinTreeNode<T>* root) {
    if (!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

template <class T>
std::vector<unsigned> isThereNiveausEqualSum(BinTreeNode<T>* root) {
    std::map<T, unsigned> setSums;
    std::vector<T> listNiveau;
    std::vector<unsigned> res;
    unsigned maxNiveau = height(root);
    for (unsigned i = 0; i < maxNiveau; ++i) {
        elementsAtLevel(root, 0, i, listNiveau);
        int sum = getSum(listNiveau);
        auto p = setSums.insert({sum, i});
        if (p.second == 0) {
            res.push_back(1);
            res.push_back(setSums[sum]);
            res.push_back(i);
            return res;
        }
        listNiveau.clear();
    }
    return res;
}

int main() {
    BinTreeNode<int>* root = new BinTreeNode<int>(7,
                                    new BinTreeNode<int>(14,
                                        new BinTreeNode<int>(1,
                                            new BinTreeNode<int>(20)),
                                        new BinTreeNode<int>(5)),
                                    new BinTreeNode<int>(6,
                                        new BinTreeNode<int>(8)));
    
    int h = height(root);                                    
    std::cout << "height: " <<  h << '\n';
    std::vector<int> list;
    for (int i = 0; i < h; ++i) {
        elementsAtLevel(root, 0, i, list);
        for (int l : list) {
            std::cout << l << ' ';
        }
        std::cout << '\n';
        list.clear();
    }
    std::vector<unsigned> res = isThereNiveausEqualSum(root);
    if (!res.empty()) {
        std::cout << "true, niveaus: " << res[1] << ' ' << res[2] << '\n';
    }
    destruct(root);
    return 0;
}