#include <iostream>
#include <set>

struct Node {
    char symbol;
    Node *left, *middle, *right;
    Node(char s, Node* l = nullptr, Node* m = nullptr, Node* r = nullptr)
        : symbol(s), left(l), middle(m), right(r)
    {}
};

void destruct(Node* root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->middle);
    destruct(root->right);
    delete root;
    //std::cout << "delete node\n";
}

bool isLeaf(Node* root) {
    if (!root) return false;
    return !root->left && !root->middle && !root->right;
}

void allStrings(Node* root, std::string& currWord, std::set<std::string>& words) {
    if (!root) return;
    currWord.push_back(root->symbol);
    if (isLeaf(root)) {
        words.insert(currWord);
        return;
    }
    allStrings(root->left, currWord, words);
    if (root->left) {
        currWord.pop_back();
    }
    allStrings(root->middle, currWord, words);
    if (root->middle) {
        currWord.pop_back();
    }
    allStrings(root->right, currWord, words);
    if (root->right) {
        currWord.pop_back();
    }
}

void print(Node* root) {
    if (!root) return;
    std::cout << root->symbol << ' ';
    print(root->left);
    print(root->middle);
    print(root->right);
}

int main() {
    Node* root = new Node('A',
                        new Node('B',
                            new Node('D'),
                            nullptr,
                            new Node('E')),
                        new Node('C'),
                        new Node('B', 
                            nullptr, 
                            new Node('D'),
                            nullptr));
    print(root); std::cout << '\n';
    std::string word;
    std::set<std::string> words;
    allStrings(root, word, words);
    for (const std::string& w : words) {
        std::cout << w << ' ';
    }
    std::cout << '\n';
    destruct(root);
    return 0;
}