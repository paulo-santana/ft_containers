#include "test_utils.hpp"
#include <map>
#include <ostream>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <utility>

#if REAL_STD
    namespace ft = std;

#else

#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

template<typename T, typename U>
static std::ostream& operator<<(std::ostream& out, ft::pair<T, U>& p) {
    out << "  pair[" << p.first << ", " << p.second << "]";
    return out;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, ft::map<T, U>& map) {
    typename ft::map<T, U>::iterator it = map.begin();
    while (it != map.end()) {
        out << *it << std::endl;
        ++it;
    }
    return out;
}

static void test_empty_constructor() {
    println("test map default constructor");

    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;
    std::cout << "int_map.size() - " << int_map.size();
    std::cout << "string_map.size() - " << string_map.size();

    std::map<int, int> int_map2((std::less<int>()));

    std::map<std::string, int> string_map2((std::less<std::string>()), std::allocator<ft::pair<std::string, int> >());

    std::cout << "int_map.size() - " << int_map2.size();
    std::cout << "string_map.size() - " << string_map2.size();
    std::cout << "at least it compiles" << std::endl;
}

static void test_size() {
    println("test map size");
    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;

    std::cout << "int_map size: " << int_map.size() << std::endl;
    std::cout << "string_map size: " << string_map.size() << std::endl;
}

static void test_range_constructor() {
    println("test map range constructor");

    ft::vector<ft::pair<int, int> > int_vec;

    for (int i = 0; i < 20; i++) {
        int_vec.push_back(ft::make_pair(20 - i, i));
    }

    ft::map<int, int> int_map(int_vec.begin(), int_vec.end());
    std::cout << "map:\n" << int_map << std::endl;
    std::cout << "map size: " << int_map.size() << std::endl;
}

static void test_copy_constructor() {
    println("test map copy constructor");

    ft::map<std::string, std::string> strmap;

    strmap.insert(ft::make_pair("c", "carac"));
    strmap.insert(ft::make_pair("b", "banab"));
    strmap.insert(ft::make_pair("a", "arara"));
    strmap.insert(ft::make_pair("d", "debed"));

    ft::map<std::string, std::string> copy_map(strmap);
    std::cout << "copy map:\n" << copy_map << std::endl;
}

static void test_assignment_operator() {
    println("test map assignment operator");

    ft::map<std::string, int> strint_map;

    strint_map.insert(ft::make_pair("mathematics", 92));
    strint_map.insert(ft::make_pair("languages", 32));
    strint_map.insert(ft::make_pair("physics", 89));
    strint_map.insert(ft::make_pair("logic", 90));
    strint_map.insert(ft::make_pair("history", 40));

    ft::map<std::string, int> map_copy;
    map_copy = strint_map;

    std::cout << "the copy:\n" << map_copy << std::endl;
}

void testMap() {
    test_empty_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_size();
}
