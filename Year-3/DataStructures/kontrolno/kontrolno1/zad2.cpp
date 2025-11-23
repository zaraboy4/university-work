#include "./zad2.hpp"
#include <iostream>

int main() {
    LinkedList<int> xs;
    for (int i = 0; i < 7; ++i) {
        xs.insertBack(i);
    }
    for (int x : xs) {
        std::cout << x << ' ';
    } std::cout << '\n';
    LinkedListIterator<int> it = xs.begin();
    std::cout << "cnt added: " << xs.InsertAfterNInterval(it, 4, 8) << '\n';
    for (int x : xs) {
        std::cout << x << ' ';
    } std::cout << '\n';
    return 0;
}