#include "test_utils.hpp"
#include <set>

#if REAL_STD
    namespace ft = std;

#else

#include "set.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

static void test_default_constructor() {
    println("test set default constructor");

    ft::set<int> int_set;
    ft::set<std::string> string_set;
    std::cout << "int_set.size() - " << int_set.size();
    std::cout << "string_set.size() - " << string_set.size();

    ft::set<int> int_set2((std::less<int>()));

    ft::set<std::string> string_set2((std::less<std::string>()), std::allocator<ft::pair<std::string, int> >());

    std::cout << "int_set.size() - " << int_set2.size();
    std::cout << "string_set.size() - " << string_set2.size();
    std::cout << "at least it compiles" << std::endl;
}

void testSet() {
    test_default_constructor();
    test_default_constructor();
}
