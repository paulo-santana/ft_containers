#include "test_utils.hpp"
#include <map>
#include <iostream>
#include <utility>

#if REAL_STD
    namespace ft = std;

#else
#include "map.hpp"
#endif

static void test_empty_constructor() {
    println("test map default constructor");

    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;
    std::cout << "at least it compiles" << std::endl;
}

static void test_size() {
    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;

    std::cout << "int_map size: " << int_map.size() << std::endl;
}

void testMap() {
    test_empty_constructor();
    test_size();
}
