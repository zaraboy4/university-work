#ifndef _AVL_TREE_HEADER
#define _AVL_TREE_HEADER

#include "../7_Binary_Search_Tree/BinSearchTree.hpp"

template <typename T>
class AVLElement {
private:
    T data;
    int balance;
    AVLElement(const T& _data, const int& _balance = 0)
        : data(_data), balance(_balance) {}
public:
    T& getData() { return data; }
    int& getBalance() { return balance; }
    
    bool operator<(const AVLElement& other) const {
        return data < other.data;
    }
    bool operator>=(const AVLElement& other) const {
        return !(*this < other);
    }
    bool operator==(const AVLElement& other) const {
        return data == other.data;
    }
    bool operator==(const AVLElement& other) const {
        return !(*this == other);
    }
    bool operator<=(const AVLElement& other) const {
        return *this < other || *this == other;
    }
    bool operator>(const AVLElement& other) const {
        return !(*this <= other);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const AVLElement<T>& el) {
    out << el.getData();
    return out;
}

template <typename T>
class AVLTree : protected BSTree<AVLElement<T>> {
private:
    void rotateLeft(BinTreeMutablePosition<AVLElement<T>> x);
};

template <typename T>
void AVLTree<T>::rotateLeft(BinTreeMutablePosition<AVLElement<T>> x) {
    BSTree<AVLElement<T>> temp;
    BinTreeMutablePosition<AVLElement<T>> y = temp.rootMutablePos();
    BSTree<AVLElement<T>>::assignFrom(y, +x);
    int& bx = (*x).getBalance();
    int& by = (*y).getBalance();
    BSTree<AVLElement<T>>::assignFrom(+x, -y);
    BSTree<AVLElement<T>>::assignFrom(-y, x);
    BSTree<AVLElement<T>>::assignFrom(x, y);
     
}

#endif