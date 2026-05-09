#ifndef _BINARY_TREE_HEADER
#define _BINARY_TREE_HEADER

#include <iostream>

template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode *left, *right;
    BinTreeNode(const T& _data, BinTreeNode* _left = nullptr, BinTreeNode* _right = nullptr)
        : data(_data), left(_left), right(_right)
    {}
};

template <typename T>
class BinTree;

template <class T>
class BinTreePosition {
    friend class BinTree<T>;
private:
    BinTreeNode<T>* ptr;
public:
    BinTreePosition(BinTreeNode<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }
    operator bool() const { return valid(); }

    BinTreePosition left() const {
        if (!valid()) {
            throw std::runtime_error("cannot move left after invalid position");
        }
        return BinTreePosition(ptr->left);
    }

    BinTreePosition right() const {
        if (!valid()) {
            throw std::runtime_error("cannot move right after invalid position");
        }
        return BinTreePosition(ptr->right);
    }

    T& get() { 
        if (!valid()) {
            throw std::runtime_error("cannot get data from invalid position");
        }
        return ptr->data;
    }
    const T& get() const { 
        if (!valid()) {
            throw std::runtime_error("cannot get data from invalid position");
        }
        return ptr->data;
    }

    BinTreePosition& operator++() {
        *this = right();
        return *this;
    }
    BinTreePosition& operator++(int) {
        BinTreeNode saved = *this;
        ++(*this);
        return saved;
    }
    BinTreePosition operator+() const { return right(); }

    BinTreePosition& operator--() {
        *this = left();
        return *this;
    }
    BinTreePosition& operator--(int) {
        BinTreeNode saved = *this;
        --(*this);
        return saved;
    }
    BinTreePosition operator-() const { return left(); }

    T& operator*() { return get(); }
    const T& operator*() const { return get(); }

    bool operator==(const BinTreePosition& oth) const {
        return valid() && oth.valid() && ptr == oth.ptr;
    }
    bool operator!=(const BinTreePosition& oth) const {
        return !(*this == oth);
    }

};

template <typename T>
class BinTreeMutablePosition {
    friend class BinTree<T>;
private:
    BinTreeNode<T>** ptr;
public:
    BinTreeMutablePosition() : ptr(nullptr) {}
    BinTreeMutablePosition(BinTreeNode<T>*& _ptr) : ptr(&_ptr) {}

    bool valid() const { return ptr != nullptr && *ptr != nullptr; }
    operator bool() const { return valid(); }

    BinTreeMutablePosition left() const {
        if (!valid()) {
            throw std::runtime_error("cannot move left after invalid pos");
        }
        return BinTreeMutablePosition((*ptr)->left);
    }
    BinTreeMutablePosition right() const {
        if (!valid()) {
            throw std::runtime_error("cannot move left after invalid pos");
        }
        return BinTreeMutablePosition((*ptr)->right);
    }
    T& get() {
        if (!valid()) {
            throw std::runtime_error("cannot get data from invalid pos");
        }
        return (*ptr)->data;
    }
    const T& get() const {
        if (!valid()) {
            throw std::runtime_error("cannot get data from invalid pos");
        }
        return (*ptr)->data;
    }

    BinTreeMutablePosition& operator--() {
        *this = left();
        return *this;
    }
    BinTreeMutablePosition& operator++() {
        *this = right();
        return *this;
    }

    BinTreeMutablePosition operator--(int) {
        BinTreeMutablePosition saved = *this;
        --(*this);
        return saved;
    }
    BinTreeMutablePosition operator++(int) {
        BinTreeMutablePosition saved = *this;
        ++(*this);
        return saved;
    }

    BinTreeMutablePosition operator-() const { return left(); }
    BinTreeMutablePosition operator+() const { return right(); }

    T& operator*() { return get(); }
    const T& operator*() const { return get(); }

    // bool operator==(const BinTreeMutablePosition& other) {
    //     std::cout << "& of pos1: " << ptr << '\n';   
    //     std::cout << "& of pos2: " << other.ptr << '\n';        
    //     return valid() && other.valid() && ptr == other.ptr;
    // }
    // bool operator!=(const BinTreeMutablePosition& other) {
    //     return !(*this == other);
    // }
};

template <typename T>
class BinTree {
private:
    BinTreeNode<T>* root;
    BinTreePosition<T> copy(BinTreePosition<T>);
    void erase(BinTreePosition<T>);
public:
    BinTree();
    BinTree(const T& el);
    BinTree(const T&, BinTree&& left, BinTree&& right);
    BinTree(BinTreeNode<T>*& _root) : root(_root) { _root = nullptr; }
    BinTree(const BinTree& oth) { copy(oth.rootPos()); }
    BinTree(BinTree&&);
    BinTree& operator=(const BinTree&);
    BinTree& operator=(BinTree&&);
    ~BinTree() { erase(rootPos()); }

    BinTree& addElement(const char* trace, const T& d);

    void print(std::ostream& out) { printHelp(rootPos(), out); }
    void printHelp(BinTreePosition<T> pos, std::ostream&);

    BinTreePosition<T> rootPos() const { return BinTreePosition<T>(root); }
    BinTreeMutablePosition<T> rootMutablePos() { return BinTreeMutablePosition<T>(root); }

    bool empty() const { return root == nullptr; }

    void assignFrom(BinTreeMutablePosition<T> base, BinTreeMutablePosition<T> other);
    // void assignFrom2(BinTreePosition<T>& base, BinTreePosition<T>& other);
};

template <typename T>
BinTree<T>::BinTree() : root(nullptr) {}

template <typename T>
BinTree<T>::BinTree(const T& el) : root(new BinTreeNode<T>(el)) {}

template <typename T>
BinTree<T>::BinTree(const T& el, BinTree&& left, BinTree&& right) : BinTree(el) {
    root->left = left.root;
    root->right = right.root;
    left.root = right.root = nullptr;
}

template <typename T>
BinTree<T>::BinTree(BinTree&& oth) : BinTree() {
    assignFrom(rootMutablePos(), oth.rootMutablePos());
}

template <typename T>
BinTree<T>& BinTree<T>::operator=(const BinTree& oth) {
    if (this != &oth) {
        erase(rootPos());
        copy(oth.rootPos());
    }
    return *this;
}

template <typename T>
BinTree<T>& BinTree<T>::operator=(BinTree&& oth) {
    if (this != &oth) {
        assignFrom(rootMutablePos(), oth.rootMutablePos());
    }
    return *this;
}

template <typename T>
BinTreePosition<T> BinTree<T>::copy(BinTreePosition<T> pos) {
    if (pos) {
        BinTreeNode<T>* left = -pos ? copy(-pos).ptr : nullptr;
        BinTreeNode<T>* right = +pos ? copy(+pos).ptr : nullptr;

        root = new BinTreeNode<T>(*pos, left, right);
    }
    return rootPos();
}

template <typename T>
void BinTree<T>::erase(BinTreePosition<T> pos) {
    if (!pos) return;
    erase(-pos);
    erase(+pos);
    delete pos.ptr;
}

template <typename T>
BinTree<T>& BinTree<T>::addElement(const char* trace, const T& el) {
    if (*trace == '\0') {
        if (!empty()) {
            throw std::runtime_error("try to insert as root, but tree is not empty");
        }
        root = new BinTreeNode<T>(el);
    }
    else {
        BinTreeNode<T>* curr = root;
        while (*trace != '\0' && *(trace + 1) != '\0') {
            if (!curr) {
                throw std::runtime_error("wrong path for inserting");
            }
            if (*trace == 'L') {
                curr = curr->left;
            }
            else if (*trace == 'R') {
                curr = curr->right;
            }
            else throw std::runtime_error("invalid character in path for inserting element");
            ++trace;
        }
        if (!curr) {
            throw std::runtime_error("wrong path for inserting");
        }
        if (*trace == 'L') {
            if (curr->left) {
                throw std::runtime_error("wrong path for inserting");
            }
            curr->left = new BinTreeNode<T>(el);
        }
        else if (*trace == 'R') {
            if (curr->right) {
                throw std::runtime_error("wrong path for inserting");
            }
            curr->right = new BinTreeNode<T>(el);
        }
        else throw std::runtime_error("invalid character in path for inserting element");
    }
    return *this;
}

template <typename T>
void BinTree<T>::printHelp(BinTreePosition<T> pos, std::ostream& out) {
    if (!pos) {
        out << "()";
        return;
    }
    out << '(';
    out << *pos << ' ';
    printHelp(-pos, out);
    out << ' ';
    printHelp(+pos, out);
    out << ')';
}

template <class T>
void BinTree<T>::assignFrom(BinTreeMutablePosition<T> base, BinTreeMutablePosition<T> other) {
    BinTreeNode<T>* saved = *base.ptr;
    *base.ptr = *other.ptr;
    *other.ptr = nullptr;
    erase(BinTreePosition<T>(saved));
}

// template <class T>
// void BinTree<T>::assignFrom2(BinTreePosition<T>& base, BinTreePosition<T>& other) {
//     BinTreeNode<int>* saved = base.ptr;
//     base.ptr = other.ptr;
//     other.ptr = nullptr;
//     // erase(BinTreePosition(saved));
// }
#endif