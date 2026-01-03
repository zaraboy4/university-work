#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "d:/uni/doctest/doctest.h"
#include "./BinaryTree.hpp"
#include <sstream>

using Node = BinTreeNode<int>; 

TEST_CASE("build tree and print it") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, nullptr,
                        new Node(6)));
    BinTree<int> tree(root);
    std::ostringstream os;
    tree.print(os);
    CHECK_EQ(os.str(), "(1 (2 (4 () ()) (5 () ())) (3 () (6 () ())))");
}

TEST_CASE("try BinTreePositon") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, nullptr,
                        new Node(6)));
    BinTree<int> tree(root);
    BinTreePosition<int> pos = tree.rootPos();
    ++(++pos);
    CHECK_EQ(*pos, 6);
    SUBCASE("navigate to invalid pos") {
        pos = tree.rootPos();
        ++(--pos);
        CHECK(*pos == 5);
        --pos;
        CHECK(pos == false);
    }
}

TEST_CASE("try BinTreeMutablePositon") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, nullptr,
                        new Node(6)));
    BinTree<int> tree(root);
    BinTreeMutablePosition<int> pos = tree.rootMutablePos();
    ++(++pos);
    CHECK_EQ(*pos, 6);
    SUBCASE("navigate to invalid pos") {
        pos = tree.rootMutablePos();
        ++(--pos);
        CHECK(*pos == 5);
        --pos;
        CHECK(pos == false);
    }
}

TEST_CASE("operator= for mutablePos") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, nullptr,
                        new Node(6)));
    BinTree<int> tree(root);
    BinTreeMutablePosition<int> pos1 = tree.rootMutablePos();
    BinTreeMutablePosition<int> pos2 = tree.rootMutablePos();
    // ++pos2;
    // std::cout << *pos2;
    // std::cout << (pos1 == pos2);
}

// TEST_CASE("try to get data from empty tree") {
//     BinTree<int> tree;
//     std::cout << *tree.rootPos();
// }

TEST_CASE("try copying a binary tree") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, 
                        new Node(7, nullptr,
                            new Node(9)),
                        new Node(6)));
    BinTree<int> tree(root);
    SUBCASE("is tree correct builded") {
        std::ostringstream os;
        tree.print(os);
        CHECK_EQ(os.str(), "(1 (2 (4 () ()) (5 () ())) (3 (7 () (9 () ())) (6 () ())))");
    }
    SUBCASE("is the memory of Node correct stolen") {
        CHECK(root == nullptr);
    }
    BinTree<int> cp(tree);
    SUBCASE("is tree correct copied") {
        std::ostringstream os;
        cp.print(os);
        CHECK_EQ(os.str(), "(1 (2 (4 () ()) (5 () ())) (3 (7 () (9 () ())) (6 () ())))");
    }
    SUBCASE("try assignment operator") {
        Node* root2 = new Node(1, new Node(2), new Node(3));
        BinTree<int> tree2(root2);
        // tree2.print(std::cout); std::cout << '\n';
        tree2 = tree;
        // tree2.print(std::cout);
    }
}

TEST_CASE("try move semantics") {
    Node* root = new Node(1, 
                    new Node(2,
                        new Node(4),
                        new Node(5)),
                    new Node(3, 
                        new Node(7, nullptr,
                            new Node(9)),
                        new Node(6)));
    BinTree<int> tree(root);
    BinTree<int> tree2(tree);
    SUBCASE("copy constructor") {
        BinTree<int> mvtree(std::move(tree));
        std::ostringstream os;
        mvtree.print(os);
        CHECK_EQ(os.str(), "(1 (2 (4 () ()) (5 () ())) (3 (7 () (9 () ())) (6 () ())))");
        CHECK_EQ(tree.empty(), true);
    }
    SUBCASE("assignment operator") {
        Node* n = new Node(20, new Node(30), new Node(40));
        BinTree<int> my_tree(n);
        std::ostringstream os1;
        my_tree.print(os1);
        CHECK_EQ(os1.str(), "(20 (30 () ()) (40 () ()))");
        my_tree = std::move(tree2);
        std::ostringstream os2;
        my_tree.print(os2);
        CHECK_EQ(os2.str(), "(1 (2 (4 () ()) (5 () ())) (3 (7 () (9 () ())) (6 () ())))");
        CHECK_EQ(tree2.empty(), true);
    }
}

TEST_CASE("modify root data with BinTreePos") {
    BinTree<int> tree(1, BinTree<int>(2), BinTree<int>(3));
    CHECK_EQ(*tree.rootPos(), 1);
    *tree.rootPos() = 10;
    CHECK_EQ(*tree.rootPos(), 10);
}

TEST_CASE("modify root data with BinTreeMutablePos") {
    BinTree<int> tree(1, BinTree<int>(2), BinTree<int>(3));
    CHECK_EQ(*tree.rootMutablePos(), 1);
    *tree.rootMutablePos() = 10;
    CHECK_EQ(*tree.rootMutablePos(), 10);
}

// TEST_CASE("assignFrom with BinTreePosition") {
//     BinTree<int> tree1(1, BinTree<int>(2), BinTree<int>(3));
//     BinTree<int> tree2(10, BinTree<int>(20), BinTree<int>(30));
//     BinTreePosition<int> pos1 = tree1.rootPos();
//     BinTreePosition<int> pos2 = tree2.rootPos(); 

    // tree1.assignFrom2(pos1, pos2);
    // CHECK_EQ(pos2.valid(), false);
// }

TEST_CASE("assignFrom with BinTreeMutablePosition") {
    BinTree<int> tree1(1, BinTree<int>(2), BinTree<int>(3));
    BinTree<int> tree2(10, BinTree<int>(20), BinTree<int>(30));
    BinTreeMutablePosition<int> pos1 = tree1.rootMutablePos();
    BinTreeMutablePosition<int> pos2 = tree2.rootMutablePos(); 

    tree1.assignFrom(pos1, pos2);
    CHECK_EQ(*pos1, 10);
    CHECK_EQ(tree2.empty(), true);
}

TEST_CASE("inserting element") {
    BinTree<int> tree;
    tree.addElement("", 2);
    SUBCASE("insert root") {
        std::ostringstream os;
        tree.print(os);
        CHECK_EQ(os.str(), "(2 () ())");
    }
    SUBCASE("insert root in not-empty tree") {
        CHECK_THROWS_AS(tree.addElement("", 10), std::runtime_error);
    }
    tree.addElement("R", 5);
    tree.addElement("RL", 7);
    SUBCASE("insert 5 (R) and 7 (RL)") {
        std::ostringstream os;
        tree.print(os);
        CHECK_EQ(os.str(), "(2 () (5 (7 () ()) ()))");
    }
    SUBCASE("insert in middle path") {
        CHECK_THROWS_AS(tree.addElement("R", 20), std::runtime_error);
    }
    SUBCASE("insert in last element of path") {
        CHECK_THROWS_AS(tree.addElement("RL", 30), std::runtime_error);
    }
    SUBCASE("insert where too long path") {
        CHECK_THROWS_AS(tree.addElement("RLRL", 40), std::runtime_error);
    }
    SUBCASE("insert -3 (RLR)") {
        tree.addElement("RLR", -3);
        std::ostringstream os;
        tree.print(os);
        CHECK_EQ(os.str(), "(2 () (5 (7 () (-3 () ())) ()))");
    }
    CHECK_THROWS_AS(tree.addElement("RL*L", 10), std::runtime_error);
}