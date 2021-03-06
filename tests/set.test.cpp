#include "test_utils.hpp"
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <vector>
#include <set>

#if REAL_STD
    namespace ft = std;
#else

#include "set.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

template <typename T, typename U, typename V>
std::ostream&  operator<<(std::ostream& out, const ft::set<T, U, V>& the_set) {
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

static void test_max_size() {
    println("test set max_size");

    ft::set<int> intset = generate_int_set();
    std::cout << "max size != 0: " << (intset.max_size() == 0) << std::endl;

    ft::set<std::string> string_set;
    std::cout << "int set max_size != string set max_size: " << (intset.max_size() != string_set.max_size()) << std::endl;
}

static void test_insert() {
    println("test set insert");

    println("insert a pair on an empty set");
    ft::set<std::string, CustomComparator<std::string> > strset;
    strset.insert("arara");
    std::cout << "set:\n" << strset;

    println("insert a pair on a set with one element");
    strset.insert("aviao");
    std::cout << "set:\n" << strset;

    println("test the return value of the insertion");
    ft::pair<ft::set<std::string, std::string>::iterator, bool> result;
    result = strset.insert("carro");
    std::cout << "result->first: " << *result.first
        << "\nresult->second: " << result.second << std::endl;

    println("insert an item with an already existing key");
    result = strset.insert("moto");
    std::cout << "result->first: " << *result.first
        << "\nresult->second: " << result.second << std::endl;

}

static void test_insert_with_hint() {
    println("test set insert with hint");

    println("insert a pair on an empty set with begin() as a hint");
    ft::set<std::string> strset;
    strset.insert(strset.begin(), "arara");
    std::cout << "set:\n" << strset;

    println("insert another pair on a set with 1 element with begin() as a hint");
    strset.insert(strset.begin(), "banana");
    std::cout << "set:\n" << strset;

    {
        ft::set<int> intset;
        println("fill a set with growing values using begin() as a hint");
        for (int i = 0; i < 20; i++) {
            intset.insert(intset.begin(), i * i);
        }
        std::cout << "set:\n" << intset;
    }
    {
        ft::set<int> intset;
        println("fill a set with growing values using end() as a hint");
        for (int i = 0; i < 20; i++) {
            intset.insert(intset.end(), i * i);
        }
        std::cout << "set:\n" << intset;
    }
    {
        ft::set<int> intset;
        println("fill a set with growing values using the last inserted element as a hint");
        ft::set<int>::iterator result = intset.insert(intset.begin(), 0);
        for (int i = 0; i < 20; i++) {
            result = intset.insert(result, i * i);
        }
        std::cout << "set:\n" << intset;
    }
    {
        ft::set<int, CustomComparator<int> > intset;
        println("fill a set with diminishing values using the last inserted element as a hint and a custom comparator");
        ft::set<int, CustomComparator<int> >::iterator result = intset.insert(intset.begin(), 0);
        for (int i = 0; i < 20; i++) {
            result = intset.insert(result, i * i);
        }
        std::cout << "set:\n" << intset;
    }

    println("insert a pair using various hints");
    for (int hint_key = 1; hint_key < 14; hint_key += 2) {
        for (int i = 0; i < 15; i += 2) {
            ft::set<int> intset;
            intset.insert(7);
            intset.insert(3);
            intset.insert(11);
            intset.insert(1);
            intset.insert(5);
            intset.insert(9);
            intset.insert(13);

            ft::set<int>::iterator hint = intset.find(hint_key);
            std::cout << "insert " << i << " with " << hint_key << " as hint" << std::endl;
            intset.insert(hint, i);
            std::cout << "set:\n" << intset << std::endl;
        }
    }
}

static void test_insert_range() {
    println("test set range insert");

    ft::vector<int> intvec;
    for (int i = 0; i < 15; i++) {
        intvec.push_back(i * i - 1);
    }

    println("insert in an empty set");
    {
        ft::set<int> intset;
        intset.insert(intvec.begin(), intvec.end());
        std::cout << "set size: " << intset.size() << std::endl;
        std::cout << "set:\n" << intset << std::endl;
    }
}

static void test_erase() {
    println("test set erase");

    ft::set<int> intset;
    for (int i = 0; i < 15; i++) {
        intset.insert(i * i * 2);
    }

    std::cout << "initial set:\n" << intset << std::endl;
    intset.erase(intset.begin());
    std::cout << "delete begin():\n" << intset << std::endl;
    intset.erase(intset.begin());
    std::cout << "delete begin():\n" << intset << std::endl;
    std::cout << "delete 99:\n";
    intset.erase(intset.find(98));
    std::cout << intset << std::endl;
    std::cout << "delete everything" << std::endl;
    while (intset.size() > 0)
        intset.erase(intset.begin()++);
    std::cout << "set: " << intset << std::endl;

}

static void test_erase_key() {
    println("test erase by key");

    ft::set<int> intset;
    for (int i = 0; i < 15; i++) {
        intset.insert(i * i * 2);
    }

    std::cout << "initial set:\n" << intset << std::endl;
    ft::set<int>::size_type result = intset.erase(-1);
    std::cout << "delete -1:\n" << intset << std::endl;
    std::cout << "result: " << result << std::endl;
    result = intset.erase(0);
    std::cout << "delete 0:\n" << intset << std::endl;
    std::cout << "result: " << result << std::endl;
    result = intset.erase(99);
    std::cout << "delete 99:\n" << intset << std::endl;
    std::cout << "delete everything" << std::endl;
    while (intset.size() > 0)
        intset.erase(--intset.end());
    std::cout << "set: " << intset << std::endl;
}

static void test_erase_range() {
    println("test set erase range");

    ft::set<int> intset;

    intset.insert(-1);
    intset.insert(0);
    intset.insert(3);
    intset.insert(8);
    intset.insert(15);
    intset.insert(24);
    intset.insert(35);
    intset.insert(48);
    intset.insert(63);
    intset.insert(80);
    intset.insert(99);
    intset.insert(120);
    intset.insert(143);
    intset.insert(168);
    intset.insert(195);

    std::cout << "initial set:\n" << intset << std::endl;
    // prettyPrint(intset.get_tree());

    ft::set<int, int>::iterator first = intset.begin();
    ft::set<int, int>::iterator last = intset.begin();
    for (int i = 0; i < 5; ++i, ++first, ++last, ++last);

    std::cout << "erase 5 nodes in the middle" << std::endl;
    intset.erase(first, last);

    std::cout << "set:\n" << intset << std::endl;

    std::cout << "erase begin to end" << std::endl;
    intset.erase(intset.begin(), intset.end());

    std::cout << "set:\n" << intset << std::endl;

}

static void test_swap() {
    println("test set swap");

    ft::set<int> myset;
    ft::set<int> otherset;

    myset.insert(1);
    myset.insert(2);
    myset.insert(3);
    myset.insert(4);

    otherset.insert(5);
    otherset.insert(6);
    otherset.insert(7);

    myset.swap(otherset);

    std::cout << "myset:\n" << myset << std::endl;
    std::cout << "otherset:\n" << otherset << std::endl;
}

static void test_clear() {
    println("test set clear");

    ft::set<int> intset;
    intset.insert(42);
    intset.insert(12);
    intset.insert(82);

    std::cout << "set before clear:\n" << intset << std::endl;
    intset.clear();
    std::cout << "set after clear:\n" << intset << std::endl;
    std::cout << "clearing an empty set" << std::endl;
    ft::set<int, int> empty;
    empty.clear();
    std::cout << "empty set after clear:\n" << empty << std::endl;
}

static void test_key_comp() {
    println("test set key_comp()");

    ft::set<int> intset;
    std::cout << "the default Comparator of a set is std::less: ";

    std::cout << (typeid(intset.key_comp()).name()) << std::endl;

    println("a set can be assigned a comparator");

    ft::set<std::string, CustomComparator<const std::string> > custom_set;
    custom_set.insert("aaa");
    custom_set.insert("bbb");
    custom_set.insert("ccc");

    std::cout << "customly comparated set:" << std::endl;

    ft::set<std::string, CustomComparator<const std::string> >::iterator iter = custom_set.begin();
    for (; iter != custom_set.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
}

static void test_value_comp() {
    println("test set value_comp()");

    ft::set<int> intset;

    intset.insert(3);
    intset.insert(2);
    intset.insert(1);

    ft::set<int>::value_compare v_compare = intset.value_comp();
    ft::set<int>::iterator tree = intset.find(3);
    ft::set<int>::iterator two = intset.find(2);

    std::cout << "set:\n" << intset << std::endl;
    std::cout << "value_comp()([3, 42], [2, 32]): " << v_compare(*tree, *two) << std::endl;
}

static void test_find() {
    println("test set find");

    ft::set<int> intset;

    for (int i = 0; i < 10; i++) {
        intset.insert(i);
    }
    std::cout << "find every element in the set" << std::endl;

    for (int i = 0; i < 10; i++) {
        ft::set<int, int>::iterator value = intset.find(i);
        if (value != intset.end())
            std::cout << *value << std::endl;
    }

    std::cout << "try find an non existent element" << std::endl;

    std::cout << "found 42: " << (intset.find(42) != intset.end()) << std::endl;
}

static void test_count() {
    println("test set count");

    ft::set<std::string> string_set;

    string_set.insert("an element");
    string_set.insert("another element");
    string_set.insert("other element");

    std::cout << "set count 'an element': " << string_set.count("an element") << std::endl;
    std::cout << "set count 'non existing element': " << string_set.count("non existing element") << std::endl;

    ft::set<int> set;
    std::cout << "count elements of an empty set: " << set.count(32) << std::endl;
}

static void test_lower_bound() {
    println("test set lower_bound");

    ft::set<char> string_set;

    string_set.insert('a');
    string_set.insert('e');
    string_set.insert('i');
    string_set.insert('o');
    string_set.insert('u');

    const ft::set<char> const_string_set = string_set;

    ft::set<char>::iterator iter = string_set.lower_bound('e');

    std::cout << "lower bound('e'): " << *iter << std::endl;
    std::cout << "lower bound('a'): " << *const_string_set.lower_bound('a') << std::endl;
    std::cout << "lower bound('u'): " << *const_string_set.lower_bound('u') << std::endl;
    iter = string_set.lower_bound('c');
    std::cout << "lower bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::set<char, std::string>::iterator nciter = const_string_set.lower_bound('e');
}

static void test_lower_bound_custom_comparator() {
    println("test set lower_bound");

    ft::set<char, CustomComparator<char> > string_set;

    string_set.insert('a');
    string_set.insert('e');
    string_set.insert('i');
    string_set.insert('o');
    string_set.insert('u');

    const ft::set<char, CustomComparator<char> > const_string_set = string_set;

    ft::set<char>::iterator iter = string_set.lower_bound('e');

    std::cout << "lower bound('e'): " << *iter << std::endl;
    std::cout << "lower bound('a'): " << *const_string_set.lower_bound('a') << std::endl;
    std::cout << "lower bound('u'): " << *const_string_set.lower_bound('u') << std::endl;
    iter = string_set.lower_bound('c');
    std::cout << "lower bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::set<char, std::string>::iterator nciter = const_string_set.lower_bound('e');
}

static void test_upper_bound() {
    println("test set upper_bound");

    ft::set<char> string_set;

    string_set.insert('a');
    string_set.insert('e');
    string_set.insert('i');
    string_set.insert('o');
    string_set.insert('u');

    const ft::set<char> const_string_set = string_set;


    std::cout << "upper bound('e'): " << *string_set.upper_bound('e') << std::endl;
    std::cout << "upper bound('a'): " << *string_set.upper_bound('a') << std::endl;
    std::cout
        << "upper bound('u') == end(): "
        << (const_string_set.upper_bound('u') == const_string_set.end())
        << std::endl;
    ft::set<char, std::string>::const_iterator iter;
    iter = const_string_set.upper_bound('c');
    std::cout << "upper bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::set<char, std::string>::iterator nciter = const_string_set.upper_bound('e');
}

static void test_equal_range() {
    println("test equal range");

    typedef ft::set<char> set;
    set string_set;

    string_set.insert('u');
    string_set.insert('o');
    string_set.insert('i');
    string_set.insert('e');
    string_set.insert('a');

    const ft::set<char> const_string_set = string_set;

    ft::pair<set::const_iterator, set::const_iterator> result;

    result = const_string_set.equal_range('e');
    set::const_iterator first = result.first;
    set::const_iterator end = result.second;

    while (first != end) {
        std::cout << "result:\n" << *first << std::endl;
        ++first;
    }
    std::cout << "peek at the end:\n" << *end << std::endl;

    ft::pair<set::iterator, set::iterator> mut_result;
    mut_result = string_set.equal_range('a');

    std::cout << "search from a non const set" << std::endl;
    first = mut_result.first;
    end = mut_result.second;
    while (first != end) {
        std::cout << "result:\n" << *first << std::endl;
        ++first;
    }
    std::cout << "peek at the end:\n" << *end << std::endl;
    // shoudn't compile:
    // mut_result = const_string_set.equal_range('i');
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
    test_max_size();

    test_insert();
    test_insert_with_hint();
    test_insert_range();

    test_erase();
    test_erase_key();
    test_erase_range();

    test_swap();
    test_clear();

    test_key_comp();
    test_value_comp();

    test_find();
    test_count();

    test_lower_bound();
    test_lower_bound_custom_comparator();
    test_upper_bound();
    test_equal_range();
}
