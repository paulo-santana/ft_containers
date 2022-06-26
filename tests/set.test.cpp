#include "test_utils.hpp"
#include <ostream>
#include <vector>
#include <set>

#if REAL_STD
    namespace ft = std;
#else

#include "set.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

template <typename T>
std::ostream&  operator<<(std::ostream& out, const ft::set<T>& the_set) {
    out << "[ ";

    typename ft::set<T>::iterator iter = the_set.begin();
    while (iter != the_set.end()) {
        out << *iter;
        ++iter;
        if (iter == the_set.end())
            out << ", ";
    }
    out << "]";
    return out;
}

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

static void test_range_constructor() {
    println("test set range constructor");

    ft::vector<int> intvec;
    for (int i = 0; i < 10; i++) {
        intvec.push_back(i);
    }

    ft::set<int> small_set(intvec.begin(), intvec.end());

    std::cout << "set: " << small_set << std::endl;
}

static void test_copy_constructor() {
    println("test set copy constructor");

    ft::vector<int> intvec;
    for (int i = 0; i < 10; i++) {
        intvec.push_back(i);
    }

    ft::set<int> small_set(intvec.begin(), intvec.end());

    ft::set<int> copy_set(small_set);

    std::cout << "set: " << copy_set << std::endl;
}

void testSet() {
    test_default_constructor();
    test_range_constructor();
    test_copy_constructor();
}
