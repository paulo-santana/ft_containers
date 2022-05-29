#include "test_utils.hpp"
#include "internals/red_black_tree.hpp"
#include <ostream>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const ft::RB_Tree &tree) {
    (void)tree;
    out << "[";

    // if (tree) {
    //
    // }

    out << " ]";

    return out;
}

static void test_default_constructor() {
    println("test RB Tree default constructor");

    ft::RB_Tree tree;

    (void)tree;
    std::cout << "at least it compiles" << std::endl;
}

void testRBTree() {
    test_default_constructor();

}
