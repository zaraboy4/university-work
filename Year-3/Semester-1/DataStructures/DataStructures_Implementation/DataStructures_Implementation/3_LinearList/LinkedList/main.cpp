#include <iostream>
#include "./LinkedList.hpp"

int main() {
    LinkedList<int> xs;
    for (int i = 0; i < 10; ++i) {
        xs.insertBack(i + 1);
    }
    LinkedList<int> ys;
    for (int i = 0; i < 10; ++i) {
        ys.insertBack(10 + i);
    }
    xs.appendAssign(std::move(ys));
    xs.print();
    ys.print();
    return 0;
}