#include "test_utils.hpp"
#include <iostream>
#if REAL_STD
# include <vector>
# include <iterator>

 typedef std::vector<int>                   vector;
 typedef std::vector<int>::iterator         iterator;
 typedef std::reverse_iterator<iterator>    reverse_iterator;

#else // !REAL_STD
# include <vector.hpp>
# include <vector/reverse_iterator.hpp>

 typedef ft::vector<int>                   vector;
 typedef ft::vector<int>::iterator         iterator;
 typedef ft::reverse_iterator<iterator>    reverse_iterator;

#endif // REAL_STD

static void test_reverse_iterator_constructors() {
    println("\ntest reverse iterator constructors");
    reverse_iterator rit;

    int values[] = {21, 42, 84};
    iterator it(values);
    reverse_iterator rit_init(it);

    reverse_iterator rit_copy(rit);

    (void)rit;
    (void)rit_copy;
}

static void test_base() {
    println("\ntest reverse iterator base()");
    int values[] = {21, 42, 84};
    iterator it(values);
    reverse_iterator rit(it);

    iterator base = rit.base();

    std::cout << "*base -> " << *base << std::endl;
    std::cout << "*it -> " << *it << std::endl;
    std::cout << "*base == *it: " << (*base == *it) << std::endl;
}

static void test_dereference_operator() {
    println("\ntest reverse iterator operator*");

    int values[] = {21, 42, 84};
    iterator it(values + 2);
    reverse_iterator rit(it);

    int value = *rit;
    std::cout << "value -> " << value << std::endl;
}

static void test_addition_operator() {
    println("\ntest reverse iterator operator+");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator it(values + 5);
    reverse_iterator rit(it);

    int value = *(rit + 2);
    std::cout << "*(rit + 2) -> " << value << std::endl;
    value = *(3 + rit);
    std::cout << "*(3 + rit) -> " << value << std::endl;
}

static void test_increment_operator() {
    println("\ntest reverse iterator operator++");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator it(values + 7);
    reverse_iterator rit(it);

    int value = *++rit;
    std::cout << "*++rit ->" << value << std::endl;
    value = *rit++;
    std::cout << "*rit++ ->" << value << std::endl;
    value = *rit;
    std::cout << "*rit ->" << value << std::endl;
}

void testReverseIterator(void) {
    test_reverse_iterator_constructors();
    test_base();
    test_dereference_operator();
    test_addition_operator();
    test_increment_operator();
}
