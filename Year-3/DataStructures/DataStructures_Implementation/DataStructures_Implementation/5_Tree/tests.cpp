#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/uni/doctest/doctest.h"
#include "./Tree.hpp"
#include <sstream>

TEST_CASE("build tree and print it") {
    Tree<int> tr1(1);
    Tree<int> tr2(2);
    Tree<int> tr3(3);
    Tree<int> tr4(4);
    tr2.addSubtree(tr3);
    tr2.addSubtree(tr4);
    tr1.addSubtree(tr2);
    // tr1.print();
}

TEST_CASE("build tree and get root") {
    Tree<int> tr1(1);
    Tree<int> tr2(2);
    Tree<int> tr3(3);
    Tree<int> tr4(4);
    tr2.addSubtree(tr3);
    tr2.addSubtree(tr4);
    tr1.addSubtree(tr2);
    CHECK_EQ(1, tr1.root());
}

TEST_CASE("build tree and get subtrees") {
    Tree<int> tr1(1);
    Tree<int> tr2(2);
    Tree<int> tr3(3);
    Tree<int> tr4(4);
    tr2.addSubtree(tr3);
    tr2.addSubtree(tr4);
    tr1.addSubtree(tr2);
    std::vector<Tree<int>> subtrees = tr1.subtrees();
    for (Tree<int> tr : subtrees) {
        CHECK_EQ(tr2.root(), tr.root());
    }
}

TEST_CASE("fancy operator<<") {
    Tree<int> tree(1);
    tree << Tree<int>(4) << Tree<int>(5) << Tree<int>(6);
    Tree<int> tr1(1);
    Tree<int> tr2(4);
    Tree<int> tr3(5);
    Tree<int> tr4(6);
    tr1.addSubtree(tr2);
    tr1.addSubtree(tr3);
    tr1.addSubtree(tr4);
    CHECK_EQ(tree, tr1);  
}

TEST_CASE("try << with ()") {
    Tree<int> tree = Tree<int>(1) << (Tree<int>(2) << (Tree<int>(3) << Tree<int>(4)));
    std::ostringstream os;
    tree.print(os);
    // tree.print(std::cout);
    CHECK_EQ(os.str(), "(1 (2 (3 (4))))");
}

TEST_CASE("build with << more complex example") {
    Tree<int> tree = Tree<int>(10) 
                        << (Tree<int>(2)
                            << Tree<int>(1) 
                            << Tree<int>(2) 
                            << Tree<int>(3))
                        << (Tree<int>(6)
                            << Tree<int>(7))
                        << (Tree<int>(9)
                            << Tree<int>(12)
                            << Tree<int>(16));
    SUBCASE("get size") {
        CHECK_EQ(tree.size(), 10);
    }
    SUBCASE("test with string") {
        std::ostringstream os;
        tree.print(os);
        CHECK_EQ(os.str(), "(10 (2 (1) (2) (3)) (6 (7)) (9 (12) (16)))");
    } 
    SUBCASE("operator=") {
        Tree<int> tree1(20);
        tree1 = tree;
        tree1 << Tree<int>(100);
        CHECK(tree1 != tree);
    }
    SUBCASE("add subtree in root") {
        Tree<int> tree2 = Tree<int>(5) 
                            << Tree<int>(4) 
                            << Tree<int>(3);
        Tree<int> cp = tree;
        cp << tree2;
        std::ostringstream os;
        cp.print(os);
        CHECK_EQ(os.str(), "(10 (2 (1) (2) (3)) (6 (7)) (9 (12) (16)) (5 (4) (3)))");
    }
    SUBCASE("add subtree deeper than root") {
        Tree<int> tree2 = Tree<int>(5) 
                            << Tree<int>(4) 
                            << Tree<int>(3);
        std::vector<Tree<int>> level1 = tree.subtrees();
        level1[1].addSubtree(tree2);
        // level1[1].print(std::cout);
    }
}

TEST_CASE("depth") {
    Tree<int> tree = Tree<int>(10) 
                        << (Tree<int>(2)
                            << Tree<int>(1) 
                            << Tree<int>(2) 
                            << Tree<int>(3))
                        << (Tree<int>(6)
                            << (Tree<int>(7) << (Tree<int>(20) << Tree<int>(23))))
                        << (Tree<int>(9)
                            << Tree<int>(12)
                            << Tree<int>(16));
    CHECK_EQ(tree.depth(), 5);
    CHECK_EQ(tree.height(), 4);
}

TEST_CASE("ostringstream") {
    std::ostringstream os;
    os << "hello";
    char text[10] = "hello";
    CHECK_EQ(os.str(), text);
    os << "!";
    CHECK(os.str() != text);
}
