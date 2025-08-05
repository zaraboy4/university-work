struct Node {
    int data;
    Node* left;
    Node* right;
    Node(const int& d = 0, Node* l = nullptr, Node* r = nullptr)
        : data(d)
        , left(l)
        , right(r)
    {}
};

void destruct(Node*& root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->right);
    delete root;
    root = nullptr;
}

void insert(Node*& root, const int& el) {
    if (!root) root = new Node(el);
    else insert(el <= root->data ? root->left : root->right, el);
}