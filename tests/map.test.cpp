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
static std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>& p) {
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

    ft::map<std::string, int> empty_map;
    ft::map<std::string, int> strint_map;

    strint_map.insert(ft::make_pair("mathematics", 92));
    strint_map.insert(ft::make_pair("languages", 32));
    strint_map.insert(ft::make_pair("physics", 89));
    strint_map.insert(ft::make_pair("logic", 90));
    strint_map.insert(ft::make_pair("history", 40));

    ft::map<std::string, int> map_copy;
    ft::map<std::string, int> empty_copy;
    map_copy = strint_map;
    empty_copy = empty_map;

    std::cout << "the empty copy:\n" << empty_copy << std::endl;
    std::cout << "the copy:\n" << map_copy << std::endl;
    std::cout << "the copy size:\n" << map_copy.size() << std::endl;
}

static void test_size() {
    println("test map size");
    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;

    std::cout << "int_map size: " << int_map.size() << std::endl;
    std::cout << "string_map size: " << string_map.size() << std::endl;
}

static void test_begin() {
    println("test map begin");

    ft::map<int, int> map;
    for (int i = 1; i < 30; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    std::cout << "map:\n" << map << std::endl;
    std::cout << "begin: " << *map.begin() << std::endl;
    std::cout << "insert pair[12, 12]" << std::endl;
    map.insert(ft::make_pair(12, 12));
    std::cout << "new begin: " << *map.begin() << std::endl;
    const ft::map<int, int> const_map = map;
    ft::map<int, int>::const_iterator const_begin = const_map.begin();

    std::cout << "const begin: " << *const_begin << std::endl;
}

static void test_end() {
    println("test map end");

    ft::map<int, int> map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int>::const_iterator iter = map.begin();
    ft::map<int, int>::const_iterator end = map.end();
    // the loop stops when it reaches the end
    for (; iter != end; ++iter) {
        std::cout << "item with key " << iter->first << ": " << iter->second << std::endl;
    }
}

static void test_rbegin() {
    println("test map rbegin");

    ft::map<int, int> map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int>::reverse_iterator riter = map.rbegin();
    // ft::map<int, int>::reverse_iterator rend = map.rbegin();

    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++riter) {
        std::cout << "item with key " << riter->first << ": " << riter->second << std::endl;
    }

    ft::map<int, int>::const_reverse_iterator criter = map.rbegin();

    std::cout << "test the const_reverse_iterator" << std::endl;
    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++criter) {
        std::cout << "item with key " << criter->first << ": " << criter->second << std::endl;
    }

}

void testMap() {
    test_empty_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_size();
    test_begin();
    test_end();
    test_rbegin();
}
