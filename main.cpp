#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <sstream>

#include "tests/tests.hpp"

#ifndef REAL_STD
# define REAL_STD 0
#endif // !REAL_STD

int main (void)
{
    if (REAL_STD)
        std::cerr << "STD containers" << std::endl;
    else
        std::cerr << "FT containers" << std::endl;

    std::map<int, int>::iterator iter;
    // std::_Rb_tree_node_base *var = iter._M_node;
    testVectorIterator();
    testReverseIterator();
    testVector();
    testStack();
    testRBTree();
    testMapIterator();
    // testPair();
    // testMap();
}
