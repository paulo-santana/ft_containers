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
        if (iter != the_set.end())
            out << ", ";
        else
            out << " ";
    }
    out << "]";
    return out;
}

static void test_default_constructor() {
    println("test set default constructor");

    ft::set<int> int_set;
    ft::set<std::string> string_set;
    std::cout << "int_set.size() - " << int_set.size() << std::endl;
    std::cout << "string_set.size() - " << string_set.size() << std::endl;

    ft::set<int> int_set2((std::less<int>()));

    ft::set<std::string> string_set2((std::less<std::string>()), std::allocator<ft::pair<std::string, int> >());

    std::cout << "int_set.size() - " << int_set2.size() << std::endl;
    std::cout << "string_set.size() - " << string_set2.size() << std::endl;
    std::cout << "at least it compiles" << std::endl;
}

static void test_range_constructor() {
    println("test set range constructor");

    ft::vector<int> intvec;
    for (int i = 10; i > 0; i--) {
        intvec.push_back(i);
    }

    ft::set<int> small_set(intvec.begin(), intvec.end());

    std::cout << "set: " << small_set << std::endl;
}

static void test_copy_constructor() {
    println("test set copy constructor");

    ft::vector<int> intvec;
    for (int i = 10; i > 0; i--) {
        intvec.push_back(i);
    }

    ft::set<int> small_set(intvec.begin(), intvec.end());

    ft::set<int> copy_set(small_set);

    std::cout << "set: " << copy_set << std::endl;
}

static void test_assignment_operator() {
    println("test set assignment operator");

    ft::vector<int> intvec;
    for (int i = 10; i > 0; i--) {
        intvec.push_back(i);
    }

    ft::set<int> small_set(intvec.begin(), intvec.end());

    ft::set<int> copy_set; 

    copy_set = small_set;
    std::cout << "set: " << copy_set << std::endl;
}

static void test_begin() {
    println("test set begin");

    ft::set<int> set;
    for (int i = 1; i < 30; i++) {
        set.insert(1000 / i);
    }

    std::cout << "set:\n" << set << std::endl;
    std::cout << "begin: " << *set.begin() << std::endl;
    std::cout << "insert 12" << std::endl;
    set.insert(12);
    std::cout << "new begin: " << *set.begin() << std::endl;
    const ft::set<int> const_set = set;
    ft::set<int, int>::const_iterator const_begin = const_set.begin();

    std::cout << "const begin: " << *const_begin << std::endl;
}

static void test_end() {
    println("test set end");

    ft::set<int> set;
    for (int i = 1; i < 30; i++) {
        set.insert(1000 / i);
    }

    for (ft::set<int>::iterator end = --set.end(); end != set.begin(); --end) {
        std::cout << "element: " << *end << std::endl;
    }
}

static ft::set<int> generate_int_set() {
    ft::set<int> intset;
    for (int i = -5; i < 5; i++) {
        intset.insert(i * 10);
    }
    return intset;
}

static void test_empty() {
    println("test set empty");

    ft::set<int> intset;
    std::cout << "set is empty: " << intset.empty() << std::endl;

    intset = generate_int_set();
    std::cout << "set is empty: " << intset.empty() << std::endl;

}

static void test_size() {
    println("test set size");

    ft::set<int> intset;
    std::cout << "empty size: " << intset.size() << std::endl;
    intset.insert(4);
    std::cout << "single size: " << intset.size() << std::endl;
    intset = generate_int_set();
    std::cout << "generated size: " << intset.size() << std::endl;
}

void testSet() {
    test_default_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_assignment_operator();

    test_begin();
    test_end();

    test_empty();
    test_size();
}
