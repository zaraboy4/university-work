#ifndef BST_TESTS
#define BST_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "d:/uni/doctest/doctest.h"
#include "./BinSearchTree.hpp"

#include <sstream>

TEST_CASE("build tree and search element") {
    BSTree<int> bst;
    int arr[8] = { 6, 3, 9, 1, 4, 2, 8, 12 };
    for (int i = 0; i < 8; ++i) {
        REQUIRE(bst.insert(arr[i]));
    }
    std::ostringstream os;
    bst.print(os);
    CHECK_EQ(os.str(), "(6 (3 (1 () (2 () ())) (4 () ())) (9 (8 () ()) (12 () ())))");
    BinTreeMutablePosition<int> pos = bst.search(4);
    CHECK_EQ(*pos, 4);
    pos = bst.search(7);
    CHECK(!pos);
    CHECK(bst.search(2));
}

TEST_CASE("remove simple cases") {
    BSTree<int> bst;
    int arr[9] = { 6, 3, 9, 1, 4, 2, 7, 8, 12 };
    for (int i = 0; i < 9; ++i) {
        REQUIRE(bst.insert(arr[i]));
    }
    bst.print(std::cout); std::cout << '\n';
    SUBCASE("remove element not in tree") {
        CHECK(!bst.remove(5));
    }
    SUBCASE("remove element without subtrees") {
        CHECK(bst.remove(4));
        bst.print(std::cout); std::cout << '\n';
    }
    SUBCASE("remove element with one subtree") {
        CHECK(bst.remove(1));
        bst.print(std::cout); std::cout << '\n';
    }
    SUBCASE("remove element with two subtrees") {
        CHECK(bst.remove(6));
        bst.print(std::cout);
    }
}

#endif