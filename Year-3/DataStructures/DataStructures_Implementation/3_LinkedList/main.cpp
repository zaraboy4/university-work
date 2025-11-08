#include "./LinkedList.hpp"

template <class T>
void print(const List<T>& xs) {
    for (int x : xs)
        std::cout << x << ' ';
    std::cout << "\n";
}

template <class T>
void test_InsertAfter(List<T>& xs) {
    // inserting after invalid iterator
    auto it1 = List<int>::Iterator(nullptr);
    xs.insertAfter(it1, 100);
    print(xs);
    // inserting after last element
    auto it2 = xs.last();
    xs.insertAfter(it2, 200);
    print(xs);
    std::cout << "last: " << *xs.last() << "\n";
    // inserting after element in middle
    auto it3 = xs.begin();
    it3 += 7;
    xs.insertAfter(it3, 300);
    print(xs);
}

template <class T>
void test_InsertBefore(List<T>& xs) {
    // auto it1 = List<int>::Iterator(nullptr);
    // xs.insertBefore(it1, 100);
    // print(xs);
    // inserting after last element
    // std::cout << *xs.last() << "|";
    // auto it2 = xs.last();
    // xs.insertBefore(it2, 200);
    // print(xs);
    // std::cout << "last: " << *xs.last() << "\n";
    // // inserting before element in middle
    List<int>::Iterator it3 = xs.begin();
    it3 += 7;
    std::cout << *xs.findPrev(it3);
    xs.insertBefore(it3, 300);
    print(xs);
}

int main() {
    List<int> xs;
    for (int i = 1; i <= 20; ++i) {
        xs.pushBack(i);
    }
    // test_InsertAfter(xs);
    test_InsertBefore(xs);
}