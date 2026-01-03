#ifndef _TREE_IMPLEMENTATION_HEADER
#define _TREE_IMPLEMENTATION_HEADER

#include <iostream>
#include <vector>

template <typename T>
class Tree {
private:
    T data;
    std::vector<Tree> trees;
public:
    Tree(const T& _data = T()) : data(_data) {}

    bool operator==(const Tree& oth) const { return data == oth.data && trees == oth.trees; }
    bool operator!=(const Tree& oth) const { return !(*this == oth); }
    void addSubtree(const Tree& tree) {
        trees.push_back(tree);
    }
    T& root() { return data; }
    const T& root() const { return data; }
    const std::vector<Tree>& subtrees() const { return trees; }
    Tree& operator<<(const Tree& tree) {
        addSubtree(tree);
        return *this;
    }
    void print(std::ostream& out = std::cout) const {
        out << '(' << root();
        for (const Tree& tree : trees) {
            out << ' ';
            tree.print(out);
        }
        out << ')';
    }
    unsigned size() const {
        unsigned s = 1;
        for (const Tree<int>& tree : trees) {
            s += tree.size();
        }
        return s;
    }
    unsigned depth() const {
        unsigned maxDepth = 0;
        for (const Tree<int>& tree : trees) {
            maxDepth = std::max(maxDepth, tree.depth());
        }
        return maxDepth + 1;
    }
    unsigned height() const {
        unsigned maxHeight = 0;
        for (const Tree<int>& tree : trees) {
            maxHeight = std::max(maxHeight, 1 + tree.height());
        }
        return maxHeight;
    }
};

#endif