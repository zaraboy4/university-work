#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "../6_BinaryTree/BinaryTree.hpp"

template <typename T>
class BSTree : public BinTree<T> {
public:
    BinTreeMutablePosition<T> searchFromPos(BinTreeMutablePosition<T> pos, const T& el);
    BinTreeMutablePosition<T> search(const T& el);
    bool insert(const T&);
    bool remove(const T&);
};

template <typename T>
BinTreeMutablePosition<T> BSTree<T>::searchFromPos(BinTreeMutablePosition<T> pos, const T& el) {
    while (pos && el != *pos) {
        if (el < *pos) {
            --pos;
        }
        else {
            ++pos;
        }
    }
    return pos;
}

template <typename T>
BinTreeMutablePosition<T> BSTree<T>::search(const T& el) {
    return searchFromPos(BinTree<T>::rootMutablePos(), el);
}

template <typename T>
bool BSTree<T>::insert(const T& el) {
    BinTreeMutablePosition<T> pos = search(el);
    if (pos) {
        return false;
    }
    BinTree<T> leaf(el);
    BinTree<T>::assignFrom(pos, leaf.rootMutablePos());
    return true;
}

template <typename T>
bool BSTree<T>::remove(const T& el) {
    BinTreeMutablePosition<T> pos = search(el);
    if (!pos) return false;
    if (!pos.left()) {
        BinTree<T>::assignFrom(pos, pos.right());
    }
    else if (!pos.right()) {
        BinTree<T>::assignFrom(pos, pos.left());
    }
    else {
        BinTreeMutablePosition<T> minRightPos = +pos;
        while (-minRightPos) {
            --minRightPos;
        }
        *pos = *minRightPos;
        BinTree<T>::assignFrom(minRightPos, +minRightPos); 
    }
    return true;
}

#endif