#include "test_utils.hpp"
#include <ostream>

#if REAL_STD
    namespace ft = std;
#else
    #include "pair.hpp"
#endif

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const ft::pair<T1, T2>& pair) {
    out << "  pair[" << pair.first << "," << pair.second << "]";
    return out;
}

static void test_default_constructor() {
    println("test pair default constructor");

    ft::pair<const int, int> item;

    std::cout << item << std::endl;
}

static void test_copy_constructor() {
    println("test pair copy constructor");

    ft::pair<const int, int> item;
    item.second = 3;

    ft::pair<const int, float> copy(item);
    std::cout << copy << std::endl;
}

static void test_initialization_constructor() {
    println("test pair initialization constructor");

    ft::pair<const std::string, int> item("first", 42);
    std::cout << item << std::endl;
}

void testPair() {
    test_default_constructor();
    test_copy_constructor();
    test_initialization_constructor();
}
