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

    std::map<int, int> map;
    for (int i = 333; i < 343; i++) { 
        map[i] = i * i;
    }
    std::map<int, int>::iterator it = map.begin();
    for (int i = 0; i < 15; i++) {
        std::cout << "*it-- -> " << (*it--).first << std::endl;
    }
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
