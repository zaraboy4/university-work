#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/uni/doctest/doctest.h"
#include "./DoubleLinkedList.hpp"

TEST_CASE("insert 10 elements") {
    DLList<int> xs;
    for (int i = 0; i < 10; ++i) {
        xs.insertBack(i);
    }
    int i = 0;
    for (int x : xs) {
        CHECK_EQ(x, i++);
    }
}

TEST_CASE("move 5 steps forward iterator") {
    DLList<int> xs;
    for (int i = 0; i < 10; ++i) {
        xs.insertBack(i);
    }
    DLList<int>::Iterator it = xs.begin();
    it += 5;
    CHECK_EQ(*it, 5);
    xs.insertAfter(it, 10);
    CHECK_EQ(*(++it), 10);
}

TEST_CASE("copying constructor") {
    DLList<int> xs;
    for (int i = 0; i < 10; ++i) {
        xs.insertBack(i);
    }

    DLList<int> ys(xs);
    DLList<int>::Iterator it1, it2;
    for (it1 = xs.begin(), it2 = ys.begin() ; it1, it2; ++it1, ++it2) {
        CHECK_EQ(*it1, *it2);
    }
    CHECK_EQ(it1, it2);
    CHECK_EQ(it1, xs.end());
}

TEST_CASE("move semantics") {
    DLList<int> xs;
    for (int i = 0; i < 10; ++i) {
        xs.insertBack(i);
    }
    DLList<int> ys;
    ys.insertBack(200);
    ys.insertBack(300);
    ys = std::move(xs);
    CHECK_EQ(xs.begin(), xs.end());
    CHECK_EQ(xs.last(), xs.end());
    int j = 0;
    for (int y : ys) {
        CHECK_EQ(y, j++);
    }
}

TEST_CASE("remove from empty list") {
    DLList<int> xs;
    auto it = xs.begin();
    CHECK_EQ(0, xs.removeAt(it));
}

TEST_CASE("remove from list with one element") {
    DLList<int> xs;
    xs.insertBack(200);
    auto it = xs.begin();
    CHECK_EQ(1, xs.removeAt(it));
    CHECK_EQ(xs.empty(), 1);
    CHECK_EQ(0, xs.removeAfter(it));
    CHECK_EQ(0, xs.removeBefore(it));
}

TEST_CASE("remove from begin in list") {
    DLList<int> xs;
    for (int i = 0; i < 5; ++i) {
        xs.insertBack(i);
    }
    CHECK_EQ(1, xs.removeFirst());
    CHECK_EQ(1, *xs.begin());
}

TEST_CASE("iterate from end to begin") {
    DLList<int> xs;
    for (int i = 0; i < 5; ++i) {
        xs.insertBack(i);
    }
    int k = 4;
    for (auto it = xs.last(); it; --it) {
        CHECK_EQ(k--, *it);
    }
}

template <class T>
bool palindrome(DLList<T>& xs) {
    typename DLList<T>::Iterator it_forward = xs.begin();
    typename DLList<T>::Iterator it_reverse = xs.last();
    while (it_forward && it_reverse) {
        if (*it_forward != *it_reverse)
            return false;
        ++it_forward;
        --it_reverse;
    }
    return true;
}

TEST_CASE("is palindrome") {
    DLList<int> xs;
    int arr[5] = { 1, 2, 3, 2, 7};
    for (int i = 0; i < 5; ++i) {
        xs.insertBack(arr[i]);
    }
    CHECK_EQ(0, palindrome(xs));
}

TEST_CASE("remove before end element") {
    DLList<int> xs;
    for (int i = 0; i < 5; ++i) {
        xs.insertBack(i);
    }
    DLList<int>::Iterator it_end = xs.end();
    CHECK_EQ(0, xs.removeBefore(it_end));
    CHECK_EQ(*xs.last(), 4);
}