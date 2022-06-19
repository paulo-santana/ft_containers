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

    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++riter) {
        std::cout << "item with key " << riter->first << ": " << riter->second << std::endl;
    }

    ft::map<int, int>::const_reverse_iterator criter = map.rbegin();

    std::cout << "test the const_reverse_iterator" << std::endl;
    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++criter) {
        std::cout << "item with key " << criter->first << ": " << criter->second << std::endl;
    }

}

static void test_rend() {
    println("test map rend");

    ft::map<int, int> map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int>::reverse_iterator rend = map.rend();

    for (; rend != map.rbegin(); --rend) {
        std::cout << "item with key " << rend->first << ": " << rend->second << std::endl;
    }

    std::cout << "test the const_reverse_iterator" << std::endl;
    ft::map<int, int>::const_reverse_iterator crend = map.rend();

    for (; crend != map.rbegin(); --crend) {
        std::cout << "item with key " << crend->first << ": " << crend->second << std::endl;
    }
}

// shoudn't compile
// static void test_reverse_iterator_quirks() {
//     println("test reverse iterator quirks");
//
//     ft::map<int, int> map;
//     for (int i = 1; i < 10; i++) {
//         map.insert(ft::make_pair(1000 / i, 12 * i));
//     }
//
//     ft::map<int, int>::reverse_iterator riter = map.rbegin();
//
//     for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++riter) {
//         std::cout << "item with key " << riter->first << ": " << riter->second << std::endl;
//     }
//
//     if (riter < map.rend()) {
//         std::cout << "this shoudn't be possible" << std::endl;
//     }
// }

static void test_empty() {
    println("test map.empty()");

    ft::map<int, int> empty_map;
    std::cout << "map empty: " << empty_map.empty() << std::endl;
    empty_map.insert(ft::make_pair(1, 3));
    std::cout << "empty after inserting?: " << empty_map.empty() << std::endl;
}

static void test_size() {
    println("test map size");
    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;

    std::cout << "int_map size: " << int_map.size() << std::endl;
    std::cout << "string_map size: " << string_map.size() << std::endl;
}

static void test_max_size() {
    println("test map max_size");

    ft::map<int, int> int_map;
    ft::map<std::string, std::string> string_map;

    if (int_map.max_size() == 0) {
        std::cout << "there's something wrong with the size" << std::endl;
    } else {
        std::cout << "at least size is not 0" << std::endl;
    }
}

static void test_access_operator() {
    println("test map operator[]");

    ft::map<std::string, int> int_map;
    int_map["physics"] = 90;
    int_map["mathematics"] = 94;
    int_map["logic"] = 89;
    int_map["history"] = 44;

    std::cout << "The map:\n" << int_map << std::endl;

    std::cout << "the 'logic' value: " << int_map["logic"] << std::endl;;

}

static void test_access_operator_cplusplus() {

  ft::map<char,std::string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

void testMap() {
    test_empty_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_begin();
    test_end();
    test_rbegin();
    test_rend();
    // test_reverse_iterator_quirks();
    test_empty();
    test_size();
    test_max_size();
    test_access_operator();
    test_access_operator_cplusplus();
}
